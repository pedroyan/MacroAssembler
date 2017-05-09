#include "LexicalScanner.h"
#include "FileLibrary.h"
#include "StringLibrary.h"
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
	SuppressErrors = false;
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

	if (line == "") {
		toReturn.isEmpty = true;
		return toReturn;
	}

	try {
		vector<string> tokens;
		StringLibrary::Tokenize(line, " ", tokens);
		toReturn = organizeTokens(tokens);

	} catch (const std::runtime_error& ex) {
		if (!SuppressErrors) {
			ShowError(ex.what());
		}
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

	auto labelIndex = firstToken.find(':');
	if (labelIndex != string::npos && labelIndex == firstToken.size()-1) { //valida a label, caso seja uma
		if (!validateToken(firstToken,Label)) {
			throwError("Token " + firstToken + " invalido", Lexic);
		}

		auto replaced = firstToken.replace(labelIndex, 1, "");
		if (replaced != "") {
			dto.Rotulo = replaced;
		} else {
			throwError("Token " + firstToken + " invalido", Lexic);
		}
	} else {
		if (!validateToken(firstToken,Operation)) {
			throwError("Token " + firstToken + " invalido", Lexic);
		}
		dto.Operacao = firstToken;
	}


	for (size_t i = 1; i < tokens.size(); i++) {
		if (dto.Operacao != "") {
			if (!validateToken(tokens[i], Operand)) {
				throwError("Token de operando " + tokens[i] + " invalido", Lexic);
			}
			StringLibrary::Tokenize(tokens[i], ",", dto.Operandos);
		} else {
			if (!validateToken(tokens[i], Operation)) {
				throwError("Token de operacao " + tokens[i] + " invalido", Lexic);
			} else if (tokens[i].find(':') != string::npos) {
				throwError("Duas labels na mesma linha", Semantic);
			}
			dto.Operacao = tokens[i];
		}
	}
	if (dto.Operacao == "") {
		throwError("A linha não possui nenhuma operacao", Semantic);
	}
	return dto;
}

void LexicalScanner::ShowError(string message) {
	ErrorPrinter::ShowError(type, fileName, assembler->GetLine(), message);
}

bool LexicalScanner::validateToken(string token, LexicalScanner::TokenType type) {
	string tokenRegex = type != Label ? "([a-zA-Z0-9,_]+)" : "([a-zA-Z0-9,_\\:]+)";
	regex rgx(tokenRegex.c_str());
	bool match = std::regex_match(token, rgx);
	return token.size() <= 50 && match && (type == TokenType::Operand || !isdigit(token[0]));
}


void LexicalScanner::throwError(string errorMessage, ErrorType typeV) {
	type = typeV;
	throw std::runtime_error(errorMessage.c_str());
}

TokensDTO::TokensDTO() {
	isEmpty = false;
	Rotulo = "";
	Operacao = "";
}
