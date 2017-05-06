#include "LexicalScanner.h"
#include "FileLibrary.h"
#include "MacroAssemblerLibraries.h"

LexicalScanner::LexicalScanner(string preFileName) {
	size_t extensionIndex = preFileName.find_last_of(".");
	if (extensionIndex == string::npos) {
		preFileName.append(".pre");
	}

	FileLibrary::VerifyFile(preFileName.c_str(), "pre", "O scanner lexico aceita somente arquivos .pre", &file);
}

LexicalScanner::~LexicalScanner() {
}

bool LexicalScanner::CanRead() {
	return file.good();
}

TokensDTO LexicalScanner::GetNextTokens() {
	TokensDTO toReturn;

	string line = getNextLine();
	while (line == "" && file.good()) {
		line = getNextLine();
	}

	if (line == "") {
		return toReturn; //Já inicializado com o valor success = false
	}

	vector<string> tokens;
	StringLibrary::Tokenize(line, " ", tokens);


	return TokensDTO();
}

void LexicalScanner::RemoveComments(string & line) {
	auto index = line.find(';');
	if (index != string::npos) {
		line = line.substr(0, index);
	}
}

string LexicalScanner::getNextLine() {
	string formatedLine;
	std::getline(file, formatedLine);
	LexicalScanner::RemoveComments(formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
}

bool LexicalScanner::validateLabelAmmount(vector<string> tokens) {
	bool hasLabel = false;
	for (auto& token : tokens) {
	}
	return false;
}

TokensDTO::TokensDTO() {
	success = false;
	rotulo = "";
	operacao = "";
}
