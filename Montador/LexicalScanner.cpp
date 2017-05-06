#include "LexicalScanner.h"
#include "FileLibrary.h"
#include "MacroAssemblerLibraries.h"
#include "Assembler.h"
#include <regex>

using std::regex;

LexicalScanner::LexicalScanner(string preFileName, Assembler* ass) {
	size_t extensionIndex = preFileName.find_last_of(".");
	if (extensionIndex == string::npos) {
		preFileName.append(".pre");
	}
	assembler = ass;
	fileName = preFileName;
	FileLibrary::VerifyFile(preFileName.c_str(), "pre", "O scanner lexico aceita somente arquivos .pre", &file);
}

LexicalScanner::~LexicalScanner() {
}

bool LexicalScanner::CanRead() {
	return file.good();
}

string LexicalScanner::GetFileName() {
	return fileName;
}

TokensDTO LexicalScanner::GetNextTokens() {
	TokensDTO toReturn;

	string line = getNextLine();
	while (line == "" && file.good()) {
		line = getNextLine();
	}

	if (line == "") {
		return toReturn; //J� inicializado com o valor success = false
	}

	try {
		vector<string> tokens;
		StringLibrary::Tokenize(line, " ", tokens);
		toReturn = organizeTokens(tokens);

	} catch (const std::runtime_error& ex) {
		LexicalError(ex.what());
	}

	return toReturn;
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

TokensDTO LexicalScanner::organizeTokens(vector<string> tokens) {
	TokensDTO dto;
	auto firstToken = tokens[0];

	if (validateToken(firstToken)) {
		auto labelIndex = firstToken.find(':');
		if (labelIndex != string::npos) { //valida a label, caso seja uma
			auto replaced = firstToken.replace(labelIndex, 1, "");
			if (replaced != "") {
				dto.rotulo = replaced;
			} else {
				throw std::runtime_error("Token " + firstToken + " invalido");
			}
		} else {
			dto.operacao = firstToken;
		}
	} else {
		throw std::runtime_error("Token " + firstToken + " invalido");
	}

	for (size_t i = 1; i < tokens.size(); i++) {
		if (dto.operacao != "") {
			dto.operandos.push_back(tokens[i]);
		} else {
			if (tokens[i].find(':') != string::npos) {
				throw std::runtime_error("Duas labels na mesma linha");
			}
			dto.operacao = tokens[i];
		}
	}

	return dto;
}

void LexicalScanner::LexicalError(string message) {
	ErrorPrinter::ShowError(ErrorPrinter::ErrorType::Lexic, fileName, assembler->GetLine(), message);
}

bool LexicalScanner::validateToken(string token) {
	regex rgx("([a-zA-Z0-9_\\:]+)");
	bool match = std::regex_match(token, rgx);
	return token.size() <= 50 && match && !isdigit(token[0]);
}

TokensDTO::TokensDTO() {
	success = false;
	rotulo = "";
	operacao = "";
}
