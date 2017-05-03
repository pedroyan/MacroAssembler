#include "PreProcessor.h"
#include "MacroAssemblerLibraries.h"
#include <sstream>
#include <regex>
#include <vector>
#include <cctype>

using std::vector;
using std::regex;
using std::regex_match;

regex equRegex("([_[:alnum:]]+)?\\:([[:space:]]+)?EQU[[:space:]]([[:space:]]+)?(.+)", std::regex_constants::icase);
regex ifRegex("IF[[:space:]](.+)", std::regex_constants::icase);
regex sectionRegex("SECTION[[:space:]](.+)", std::regex_constants::icase);
regex beginRegex("((.+)[[:space:]])?BEGIN", std::regex_constants::icase);

PreProcessor::PreProcessor(string inputFileName,string outputFileName) {
	lineCount = 0;
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
	failed = false;
	preProcessingZone = true;
}


PreProcessor::~PreProcessor() {
}

void PreProcessor::PreProcessPass(istream& stream) {
	string line;
	bool writeThisDown;
	vector<string> tokens;

	while (stream.good()) {

		tokens.clear();
		writeThisDown = true;

		line = getNextLine(stream);

		StringLibrary::Tokenize(line, " ",tokens);
		if (preProcessingZone && tokens.size() >1) {
			preProcessingZone = !(StringLibrary::ToLower(tokens[0]) == "section");
		}

		if (regex_match(line,equRegex)) {
			insertOnTable(line);
			writeThisDown = false;
		} else if (regex_match(line,ifRegex)) {
			writeThisDown = evaluateIf(line, stream);
		}

		removeComments(line);

		if (writeThisDown && !preProcessingZone) {
			outputContent << line + "\n";
		}
	}

	if (!failed) {
		saveFile();
	} else {
		printf("Erros de pre-processamento encontrados. O arquivo .pre nao foi gerado\n");
	}

	return;
}

void PreProcessor::insertOnTable(string atributionLine) {

	if (!preProcessingZone) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo");
		return;
	}

	vector<string> stringDivision;

	StringLibrary::Tokenize(atributionLine, ":", stringDivision);

	string identifier = stringDivision[0];
	if (valueTable.find(identifier) != valueTable.end()) {
		string errorMessage = "Simbolo textual " + identifier + " ja definido.";
		printError(errorMessage);
		return;
	}

	if (isdigit(identifier[0])) {
		string errorMessage = "Identificador " + identifier + " invalido. Primeiro caractere nao pode ser um digito";
		printError(errorMessage);
	}

	if (identifier.size() > 50) {
		string errorMessage = "Simbolo textual nao deve possuir mais de 50 caracteres.";
		printError(errorMessage);
	}

	string expression = stringDivision[1];

	stringDivision.clear();

	StringLibrary::Tokenize(expression, " ", stringDivision);
	if (stringDivision.size() > 2) {
		printError("EQU deve possuir apenas 1 operando");
		return;
	}

	if (!StringLibrary::IsInteger(stringDivision[1])) {
		printError("Operando do EQU precisa ser um inteiro");
		return;
	}

	int valueNumber = std::stoi(stringDivision[1], nullptr);

	valueTable.emplace(std::make_pair(identifier, valueNumber));
}

bool PreProcessor::evaluateIf(string & line, istream & stream) {
	vector<string> members;
	StringLibrary::Tokenize(line, " ", members);

	if (members.size() != 2) {
		string errorMessage = "A diretiva if deve possuir somente 1 operando";
		printError(errorMessage);
		return false;
	}

	auto element = valueTable.find(members[1]);
	if (element == valueTable.end()) {
		string errorMessage = "Simbolo " + members[1] + " nao definido";
		printError(errorMessage);
		return false;
	}
	line = getNextLine(stream);
	return element->second == 1;
}

void PreProcessor::removeComments(string & line) {
	auto index = line.find(';');
	if (index != string::npos) {
		line = line.substr(0, index);
	}
}

string PreProcessor::getNextLine(istream & stream) {
	lineCount++;

	string formatedLine;
	std::getline(stream, formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
}

void PreProcessor::printError(string message) {
	failed = true;
	printf("Error %s(%d): %s\n", inputFileName.c_str(), lineCount, message.c_str());
}

void PreProcessor::saveFile() {
	fstream outputStream;
	string fileName = outputFileName + ".pre";

	outputStream.open(fileName, std::fstream::out);
	outputStream << outputContent.rdbuf();
	outputStream.close();
}
