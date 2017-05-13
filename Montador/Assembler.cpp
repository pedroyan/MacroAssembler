#include "Assembler.h"
#include "ErrorPrinter.h"
#include "StringLibrary.h"
#include <regex>

using std::regex;
using std::regex_match;

Assembler::Assembler(string outFileName) : scanner(outFileName,this) {
	outputFileName = outFileName;
	positionCount = 0;
	lineCount = 1;
	successAssemble = true;
	sectionFlags = 0;
	beginFlags = 0;
}

Assembler::~Assembler() {
}

int Assembler::GetLine() {
	return lineCount;
}

int Assembler::ExecuteDirective(string directiveName, DirectiveInfo const * info, vector<string> operands, SymbolInfo* symbol) {
	int positionSkip = 0;
	int opsize = operands.size();

	if ((info->operandCount != -1 && info->operandCount != opsize) || (info->operandCount == -1 && opsize != 0 && opsize != 1)) {
		ShowError("Diretiva invalida: Quantidade de operandos errada.",Syntatic);
		return 0;
	}

	if (directiveName  == "section") {
		positionSkip = ExecuteSection(operands);
	} else if (directiveName == "space") {
		if (symbol == nullptr) {
			ShowError("Nenhum rotulo definido para a diretiva space", Syntatic);
			return 0;
		}

		if (opsize == 0) {
			positionSkip = 1;
		} else {
			auto argument = operands[0];
			int toReturn;

			if (TryStringToInt(argument, &toReturn)) {
				symbol->spaceCount = toReturn;
				return toReturn;
			} else {
				ShowError("Operando Invalido:" + argument, Syntatic);
			}
		}
	} else if (directiveName == "extern") {
		// Modifica o rotulo passado na tabela de simbolos com o valor 0
		// e com a flag externa setada
		if (symbol == nullptr) {
			ShowError("Nenhum rótulo foi definido para a diretiva Extern",Syntatic);
			return 0;
		}
		symbol->vlr = 0;
		symbol->externo = true;
	} else if (directiveName == "public") {
		//insere o operando na tabela de definicoes
		TableManager::InsertDefinition(operands[0]);
	} else if (directiveName == "begin") {
		if (beginFlags & Begin) {
			ShowError("Siretiva begin redefinida", Semantic);
			return 0;
		}
		beginFlags = Begin;
	} else if (directiveName == "end") {
		if (!beginFlags & Begin) {
			ShowError("End não possui um Begin correspondente",Semantic);
			return 0;
		}

		if (beginFlags & BeginFlags::End) {
			ShowError("Diretiva end redefinida", Semantic);
			return 0;
		}

	} else {
		positionSkip = info->size;
	}
	return positionSkip;
}

void Assembler::Assemble() {
	firstPass();
	scanner.RestartStream();
	scanner.SuppressErrors = true;
	secondPass();
}

void Assembler::firstPass() {
	while (scanner.CanRead()) {
		auto dto = scanner.GetNextTokens();
		if (dto.Operacao=="") {
			if (!dto.isEmpty) {
				successAssemble = false;
			}
			lineCount++;
			continue;
		}
		
		SymbolInfo* symbolCreated = nullptr;
		if (dto.Rotulo != "") {
			auto symbol = TableManager::GetSymbol(dto.Rotulo);
			if (symbol != nullptr) {
				ShowError("Simbolo " + dto.Rotulo + "redefinido", ErrorType::Semantic);
			} else {
				symbolCreated = TableManager::InsertSymbol(dto.Rotulo, SymbolInfo(positionCount, false));
			}
		}

		auto instruction = TableManager::GetInstruction(dto.Operacao);
		if (instruction != nullptr) {
			positionCount += instruction->operandCount + 1;
		} else {
			auto directive = TableManager::GetDirective(dto.Operacao);
			if (directive != nullptr) {
				positionCount += ExecuteDirective(dto.Operacao, directive,dto.Operandos, symbolCreated);
			} else {
				ShowError("Operacao " + dto.Operacao + " nao identificada", ErrorType::Syntatic);
			}
		}
		lineCount++;
	}

	setDefinitionTableValues();
	TableManager::Diagnostic_PrintSymbols();
	TableManager::Diagnostic_PrintDefinitions();
}

void Assembler::secondPass() {
	positionCount = 0;
	lineCount = 1;

	while (scanner.CanRead()) {
		auto dto = scanner.GetNextTokens();
		if (!CheckLabels(dto.Operandos)) {
			continue;
		}
		
		//Para cada operando que é símbolo -> Procura operando na TS -> Se não achou:Erro, símbolo indefinido
	}
}

void Assembler::ShowError(string message, ErrorType type) {
	successAssemble = false;
	ErrorPrinter::ShowError(type, scanner.GetFileName(), lineCount, message);
}

int Assembler::ExecuteSection(vector<string> operands) {
	if (operands[0] == "text") {
		if (sectionFlags & Text) {
			ShowError("SECTION TEXT ja definida", ErrorType::Semantic);
			return 0;
		}
		sectionFlags = Text;
	} else if (operands[0] == "data") {

		if (sectionFlags & Data) {
			ShowError("SECTION DATA ja definida", ErrorType::Semantic);
			return 0;
		}

		if (!(sectionFlags & Text)) {
			ShowError("SECTION DATA definida antes de SECTION TEXT", ErrorType::Semantic);
			return 0;
		}

		sectionFlags = sectionFlags | Data;
	} else {
		ShowError("Diretiva Invalida: SECTION nao indentificada.", Syntatic);
	}
	return 0;
}

bool Assembler::TryStringToInt(string s, int* result) {
	if (StringLibrary::IsInteger(s)) {
		*result = std::stoi(s, nullptr);
		return true;
	} else if (StringLibrary::IsHexadecimal(s)) {
		*result = StringLibrary::ConvertHexaToInt(s);
		return true;
	} else {
		return false;
	}
}

void Assembler::setDefinitionTableValues() {
	auto& table = TableManager::GetDefinitionTable();
	for (auto& it : table) {
		auto symbol = TableManager::GetSymbol(it.first);

		if (symbol != nullptr) {
			it.second = symbol->vlr;
		} else {
			ShowError("O simbolo publico " + it.first + " não foi definido", Semantic);
		}
	}
}

bool Assembler::CheckLabels(const vector<string>& operands) {

	// Vai inserir o valor calculado de cada operando para a geração do codigo objeto
	bool success = true;
	for (auto& operando : operands) {
		auto type = GetType(operando);
		if (type == label) {
			auto symbol = TableManager::GetSymbol(operando);
			if (symbol == nullptr) {
				ShowError("Simbolo indefinido: " + operando, Syntatic); 
				success = false;
			}
		}
	}
	return success;
}

Assembler::operandTypes Assembler::GetType(string operand) {
	regex numberRegex("[0-9]+");
	regex operatorRegex("[\\+-]");
	if (regex_match(operand,numberRegex)) {
		return operandTypes::number;
	}

	if (regex_match(operand, operatorRegex)) {
		return operandTypes::operation;
	}

	return operandTypes::label;
}

