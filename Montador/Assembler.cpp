#include "Assembler.h"
#include "ErrorPrinter.h"
#include "StringLibrary.h"

Assembler::Assembler(string outFileName) : scanner(outFileName,this) {
	outputFileName = outFileName;
	positionCount = 0;
	lineCount = 1;
	successAssemble = true;
	sectionFlags = None;
}

Assembler::~Assembler() {
}

int Assembler::GetLine() {
	return lineCount;
}

int Assembler::ExecuteDirective(string directiveName, DirectiveInfo const * info, vector<string> operands) {
	int positionSkip = 0;
	int opsize = operands.size();

	if ((info->operandCount != -1 && info->operandCount != opsize) || (info->operandCount == -1 && opsize != 0 && opsize != 1)) {
		ShowError("Diretiva invalida: Quantidade de operandos errada.",Syntatic);
		return 0;
	}

	if (directiveName  == "section") {
		positionSkip = ExecuteSection(operands);
	} else if (directiveName == "space") {
		if (opsize == 0) {
			positionSkip = 1;
		} else {
			auto argument = operands[0];
			int toReturn;

			if (TryStringToInt(argument, &toReturn)) {
				return toReturn;
			} else {
				ShowError("Operando Invalido:" + argument, Syntatic);
			}
		}
	} else if (directiveName == "extern") {
		// Insere o rotulo passado na tabela de simbolos com o valor 0
		// e com a flag externa setada
		TableManager::InsertSymbol(operands[0], SymbolInfo(0, true));
	} else if (directiveName == "public") {
		//insere o operando na tabela de definicoes

	} else if (directiveName == "begin" || directiveName == "end") {

	} else {
		positionSkip = info->size;
	}
	return positionSkip;
}

void Assembler::Assemble() {
	firstPass();
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
		
		if (dto.Rotulo != "") {
			auto symbol = TableManager::GetSymbol(dto.Rotulo);
			if (symbol != nullptr) {
				ShowError("Simbolo " + dto.Rotulo + "redefinido", ErrorType::Semantic);
			} else {
				TableManager::InsertSymbol(dto.Rotulo, SymbolInfo(positionCount,false));
			}
		}

		auto instruction = TableManager::GetInstruction(dto.Operacao);
		if (instruction != nullptr) {
			positionCount += instruction->operandCount + 1;
		} else {
			auto directive = TableManager::GetDirective(dto.Operacao);
			if (directive != nullptr) {
				positionCount += ExecuteDirective(dto.Operacao, directive,dto.Operandos); // IMPLEMENTAR
			} else {
				ShowError("Operacao " + dto.Operacao + " nao identificada", ErrorType::Syntatic);
			}
		}
		lineCount++;
	}
	//preenche a tabela de definicoes com os valores dos simbolos
	//publicos calculados na tabela de simbolos
	setDefinitionTableValues();
	TableManager::Diagnostic_PrintSymbols();
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
	auto table = TableManager::GetDefinitionTable();
	for (auto& it : table) {
		auto symbol = TableManager::GetSymbol(it.first);

		if (symbol != nullptr) {
			it.second = symbol->vlr;
		} else {
			ShowError("O simbolo publico " + it.first + " não foi definido", Semantic);
		}
	}
}
