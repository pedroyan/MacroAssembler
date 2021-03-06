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

	while (line == "" && file.good()) {
		line = getNextLine();
	}

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

void LexicalScanner::RestartStream() {
	file.clear();
	file.seekg(0, std::ios::beg);
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
	formatedLine = StringLibrary::ToLower(formatedLine);
	LexicalScanner::RemoveComments(formatedLine);
	formatedLine = StringLibrary::Trim(formatedLine);
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

			//analisa se existe sinal de + como um token isolado
			auto plus = std::find(tokens.begin(), tokens.end(), "+");
			if (plus != tokens.end()) {
				throwError("Operador + nao pode ter espaco separando seus operandos", Lexic);
			}

			//analisa no token atual se tem algum sinal de + no seu come�o ou no seu final
			auto plusIndexBegin = tokens[i].find_first_of("+");
			auto plusIndexEnd = tokens[i].find_last_of("+");
			if (plusIndexBegin == 0 || plusIndexEnd == tokens[i].size() - 1) {
				throwError("Operador + nao pode ter espaco separando seus operandos", Lexic);
			}


			if (dto.Operacao == "copy") {
				vector<string> copyArguments;
				StringLibrary::Tokenize(tokens[i], ",", copyArguments);

				if (tokens[i].find(',') == string::npos) {
					throwError("Instrucao copy precisa ter os seus argumentos separados por virgula, sem espaco entre eles\n", Semantic);
				}

				if (copyArguments.size() != 2) {
					throwError("Instrucao copy possui somente 2 argumentos separados por virgula", Semantic);
				}

				if (!dto.Operandos.empty()) {
					throwError("Instrucao copy n�o pode ter argumentos separados por espa�o", Semantic);
				}
			}

			vector<string> copyArguments;
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
		throwError("A linha n�o possui nenhuma operacao", Semantic);
	}
	return dto;
}

void LexicalScanner::ShowError(string message) {
	ErrorPrinter::ShowError(type, fileName, assembler->GetLine(), message);
}

bool LexicalScanner::validateToken(string token, LexicalScanner::TokenType type) {
	string tokenRegex = type != Label ? "([a-zA-Z0-9,_\\+-]+)" : "([a-zA-Z0-9,_\\:]+)";
	regex rgx(tokenRegex.c_str());

	bool tokenMatch = std::regex_match(token, rgx);

	return token.size() <= 50 && tokenMatch && (type == TokenType::Operand || !isdigit(token[0]));
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
