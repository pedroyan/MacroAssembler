#include "PreProcessor.h"
#include "StringLibrary.h"
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
			auto newTokens = StringLibrary::Tokenize(line, " ");
			for (auto& toke : newTokens){
				toke = transformEQU(toke);
			}
			line = "";
			
			for (size_t i = 0; i < newTokens.size();) {
				line.append(newTokens[i]);
				i++;
				if (i<newTokens.size()) {
					line.append(" ");
				}
			}

			if (outputContent.rdbuf() -> in_avail() == 0) {
				outputContent << line;
			} else {
				outputContent << "\n" + line;
			}
			tokens.clear();
			
		}
	}

	stream.close();

	if (failed) {
		printf("Erros de pre-processamento encontrados. O arquivo .pre nao foi gerado\n");
		return false;
	} 
		
	printf("arquivo %s.pre gerado com sucesso\n", outputFileName.c_str());
	saveFile();
	return true;
}

void PreProcessor::EvaluateEQU(const vector<string>& equTokens) {

	if (!preProcessingZone) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo", ErrorType::Syntatic);
		return;
	}

	string identifier = equTokens[0].substr(0, equTokens[0].find(':'));
	if (valueTable.find(identifier) != valueTable.end()) {
		string errorMessage = "Simbolo textual " + identifier + " ja definido.";
		printError(errorMessage,ErrorType::Semantic);
		return;
	}

	if (isdigit(identifier[0])) {
		string errorMessage = "Identificador " + identifier + " invalido. Primeiro caractere nao pode ser um digito";
		printError(errorMessage, ErrorType::Lexic);
	}

	if (identifier.size() > 50) {
		string errorMessage = "Simbolo textual nao deve possuir mais de 50 caracteres.";
		printError(errorMessage,ErrorType::Lexic);
	}

	if (equTokens.size() > 3) {
		printError("EQU deve possuir apenas 1 operando", ErrorType::Syntatic);
		return;
	}

	if (!StringLibrary::IsInteger(equTokens[2])) {
		printError("Operando do EQU precisa ser um inteiro", ErrorType::Semantic);
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
		printError(errorMessage,ErrorType::Semantic);
		return false;
	}

	auto element = valueTable.find(members[1]);
	if (element == valueTable.end()) {
		string errorMessage = "Simbolo " + members[1] + " nao definido";
		printError(errorMessage,ErrorType::Semantic);
		return false;
	}
	line = getNextLine(stream);

	vector<string> tokens;
	StringLibrary::Tokenize(line, " ", tokens);
	if (IsEQU(tokens)) {
		printError("Diretiva EQU precisa ser definida no inicio do codigo",ErrorType::Semantic);
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

void PreProcessor::printError(string message, ErrorType type) {
	failed = true;
	ErrorPrinter::ShowError(type, inputFileName, lineCount, message);
}

string PreProcessor::transformEQU(string token) {
	auto tokensT = StringLibrary::Tokenize(token, "+");
	
	for (auto& toke : tokensT) {
		auto& iterator = valueTable.find(toke);
		if (iterator != valueTable.end()) {
			toke = std::to_string(iterator->second);
		}
	}

	string resultString;
	int tokenSize = tokensT.size();
	for (size_t i = 0; i < tokenSize;) {
		resultString.append(tokensT[i]);
		i++;

		if (i<tokenSize) {
			resultString.append("+");
		}
	}

	return resultString;

	//if (tokensT.size == 1) {
	//	auto iterator = valueTable.find(token);
	//	if (iterator == valueTable.end()) {
	//		return token;
	//	} else {
	//		return std::to_string(iterator->second);
	//	}
	//}
	/*tokensT.clear();*/
}



void PreProcessor::saveFile() {
	fstream outputStream;
	string fileName = outputFileName + ".pre";

	outputStream.open(fileName, std::fstream::out);
	outputStream << outputContent.rdbuf();
	outputStream.close();
}
