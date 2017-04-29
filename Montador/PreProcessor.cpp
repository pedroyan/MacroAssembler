#include "PreProcessor.h"
#include "MacroAssemblerLibraries.h"
#include <sstream>
#include <regex>
#include <vector>

using std::vector;
using std::regex;
using std::regex_match;

regex equRegex("[^[:digit:]]([_[:alnum:]]+)?\\:([[:space:]]+)?EQU[[:space:]]([[:space:]]+)?([[:digit:]]+)([[:space:]]+)?");
regex ifRegex("IF[[:space:]](.+)");
PreProcessor::PreProcessor(string inputFileName,string outputFileName) {
	lineCount = 0;
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
	failed = false;
}


PreProcessor::~PreProcessor() {
}

void PreProcessor::PreProcessPass(istream& stream) {
	string line;
	bool writeThisDown;
	while (stream.good()) {

		writeThisDown = true;
		line = getNextLine(stream);

		if (regex_match(line,equRegex)) {
			insertOnTable(line);
			writeThisDown = false;
		} else if (regex_match(line,ifRegex,std::regex_constants::match_any)) {
			writeThisDown = evaluateIf(line, stream);
		}

		if (writeThisDown) {
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

	vector<string> stringDivision;

	StringLibrary::Split(atributionLine, ":", stringDivision);

	string identifier = stringDivision[0];

	if (valueTable.find(identifier) != valueTable.end()) {
		string errorMessage = "Simbolo textual " + identifier + " ja definido.";
		printError(errorMessage);
		return;
	}

	if (identifier.size() > 50) {
		string errorMessage = "Simbolo textual nao deve possuir mais de 50 caracteres.";
		printError(errorMessage);
	}

	string expression = stringDivision[1];

	stringDivision.clear();

	StringLibrary::Split(expression, " ", stringDivision);
	int valueNumber = std::stoi(stringDivision[1], nullptr);

	valueTable.emplace(std::make_pair(identifier, valueNumber));
}

bool PreProcessor::evaluateIf(string & line, istream & stream) {
	vector<string> members;
	StringLibrary::Split(line, " ", members);

	if (members.size() != 2) {
		string errorMessage = "A diretiva if deve possuir somente 1 operando";
		printError(errorMessage);
		return true;
	}
	return false;
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
