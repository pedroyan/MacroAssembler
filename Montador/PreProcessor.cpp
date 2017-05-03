#include "PreProcessor.h"
#include "MacroAssemblerLibraries.h"
#include <sstream>
#include <regex>
#include <cctype>

using std::regex;
using std::regex_match;

regex labelRegex("(.+)?\\:");
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

bool PreProcessor::PreProcessPass(istream& stream) {
	string line;
	bool writeThisDown;
	vector<string> tokens;

	while (stream.good()) {

		tokens.clear();
		writeThisDown = true;

		line = getNextLine(stream);
		removeComments(line);

		StringLibrary::Tokenize(line, " ",tokens);

		if (tokens.size() < 1) {
			continue; // ignora linhas sem tokens
		}

		if (preProcessingZone && tokens.size() >1) {
			preProcessingZone = !(StringLibrary::CompareInsensitive(tokens[0],"section") || (StringLibrary::CompareInsensitive(tokens[0],"begin") || StringLibrary::CompareInsensitive(tokens[1], "begin")));
		}

		if (IsEQU(tokens)) {
			EvaluateEQU(tokens);
			writeThisDown = false;
		} else if (regex_match(line,ifRegex)) {
			writeThisDown = EvaluateIf(line, stream);
		}

		
		line = StringLibrary::Trim(line);

		if (writeThisDown && line != "") {
			outputContent << line + "\n";
		}
	}

	if (!failed) {
		printf("arquivo %s.pre gerado com sucesso", outputFileName.c_str());
		saveFile();
		return true;
	} else {
		printf("Erros de pre-processamento encontrados. O arquivo .pre nao foi gerado\n");
		return false;
	}
}

void PreProcessor::EvaluateEQU(const vector<string>& equTokens) {

	if (!preProcessingZone) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo");
		return;
	}

	string identifier = equTokens[0].substr(0, equTokens[0].find(':'));
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

	if (equTokens.size() > 3) {
		printError("EQU deve possuir apenas 1 operando");
		return;
	}

	if (!StringLibrary::IsInteger(equTokens[2])) {
		printError("Operando do EQU precisa ser um inteiro");
		return;
	}

	int valueNumber = std::stoi(equTokens[2], nullptr);

	valueTable.emplace(std::make_pair(identifier, valueNumber));
}

bool PreProcessor::IsEQU(vector<string> tokensLidos) {
	return tokensLidos.size() > 1 && regex_match(tokensLidos[0], labelRegex) && StringLibrary::CompareInsensitive(tokensLidos[1], "equ");
}

bool PreProcessor::EvaluateIf(string & line, istream & stream) {
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

	vector<string> tokens;
	StringLibrary::Tokenize(line, " ", tokens);
	if (IsEQU(tokens)) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo");
	}

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
