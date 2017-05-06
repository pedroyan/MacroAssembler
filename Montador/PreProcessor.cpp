#include "PreProcessor.h"
#include "MacroAssemblerLibraries.h"
#include "LexicalScanner.h"
#include <sstream>
#include <regex>
#include <cctype>

using std::regex;
using std::regex_match;

regex labelRegex("(.+)?\\:");
regex ifRegex("IF[[:space:]](.+)", std::regex_constants::icase);

PreProcessor::PreProcessor(string inputFileName,string outputFileName) {
	lineCount = 0;
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
	failed = false;
	preProcessingZone = true;
}


PreProcessor::~PreProcessor() {
}

bool PreProcessor::PreProcessPass(ifstream& stream) {
	string line;
	bool writeThisDown;
	vector<string> tokens;

	while (stream.good()) {

		tokens.clear();
		writeThisDown = true;

		line = getNextLine(stream);

		StringLibrary::Tokenize(line, " ",tokens);

		if (tokens.size() < 1) {
			continue; // ignora linhas sem tokens
		}

		if (preProcessingZone && tokens.size() >1) {
			preProcessingZone = !((tokens[0] == "section") || (tokens[0] == "begin" || tokens[1] == "begin"));
		}

		if (IsEQU(tokens)) {
			EvaluateEQU(tokens);
			writeThisDown = false;
		} else if (StringLibrary::CompareInsensitive(tokens[0],"if")) {
			writeThisDown = EvaluateIf(line, stream);
		}

		
		line = StringLibrary::Trim(line);

		if (writeThisDown && line != "") {
			outputContent << line + "\n";
		}
	}

	stream.close();

	if (failed) {
		printf("Erros de pre-processamento encontrados. O arquivo .pre nao foi gerado\n");
		return false;
	} 
		
	printf("arquivo %s.pre gerado com sucesso", outputFileName.c_str());
	saveFile();
	return true;
}

void PreProcessor::EvaluateEQU(const vector<string>& equTokens) {

	if (!preProcessingZone) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo", ErrorPrinter::ErrorType::Syntatic);
		return;
	}

	string identifier = equTokens[0].substr(0, equTokens[0].find(':'));
	if (valueTable.find(identifier) != valueTable.end()) {
		string errorMessage = "Simbolo textual " + identifier + " ja definido.";
		printError(errorMessage,ErrorPrinter::ErrorType::Semantic);
		return;
	}

	if (isdigit(identifier[0])) {
		string errorMessage = "Identificador " + identifier + " invalido. Primeiro caractere nao pode ser um digito";
		printError(errorMessage,ErrorPrinter::ErrorType::Lexic);
	}

	if (identifier.size() > 50) {
		string errorMessage = "Simbolo textual nao deve possuir mais de 50 caracteres.";
		printError(errorMessage,ErrorPrinter::ErrorType::Lexic);
	}

	if (equTokens.size() > 3) {
		printError("EQU deve possuir apenas 1 operando", ErrorPrinter::ErrorType::Syntatic);
		return;
	}

	if (!StringLibrary::IsInteger(equTokens[2])) {
		printError("Operando do EQU precisa ser um inteiro", ErrorPrinter::ErrorType::Semantic);
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
		printError(errorMessage,ErrorPrinter::ErrorType::Semantic);
		return false;
	}

	auto element = valueTable.find(members[1]);
	if (element == valueTable.end()) {
		string errorMessage = "Simbolo " + members[1] + " nao definido";
		printError(errorMessage,ErrorPrinter::ErrorType::Semantic);
		return false;
	}
	line = getNextLine(stream);

	vector<string> tokens;
	StringLibrary::Tokenize(line, " ", tokens);
	if (IsEQU(tokens)) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo",ErrorPrinter::ErrorType::Semantic);
	}

	return element->second == 1;
}


string PreProcessor::getNextLine(istream & stream) {
	lineCount++;

	string formatedLine;
	std::getline(stream, formatedLine);
	formatedLine = StringLibrary::ToLower(formatedLine);
	LexicalScanner::RemoveComments(formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
}

void PreProcessor::printError(string message, ErrorPrinter::ErrorType type) {
	failed = true;
	ErrorPrinter::ShowError(type, inputFileName, lineCount, message);
}

void PreProcessor::saveFile() {
	fstream outputStream;
	string fileName = outputFileName + ".pre";

	outputStream.open(fileName, std::fstream::out);
	outputStream << outputContent.rdbuf();
	outputStream.close();
}
