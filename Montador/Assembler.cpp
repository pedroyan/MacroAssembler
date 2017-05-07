#include "Assembler.h"
#include "ErrorPrinter.h"

Assembler::Assembler(string outFileName) : scanner(outFileName,this) {
	outputFileName = outFileName;
	positionCount = 0;
	lineCount = 1;
	successAssemble = true;
}

Assembler::~Assembler() {
}

int Assembler::GetLine() {
	return lineCount;
}

int Assembler::ExecuteDirective(string directiveName, DirectiveInfo const * info) {
	return 0;
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
			if (symbol != -1) {
				ErrorPrinter::ShowError(ErrorType::Syntatic, outputFileName, lineCount, "Simbolo " + dto.Rotulo + "redefinido");
			} else {
				TableManager::InsertSymbol(dto.Rotulo, positionCount);
			}
		}

		auto instruction = TableManager::GetInstruction(dto.Operacao);
		if (instruction != nullptr) {
			positionCount += instruction->operandCount + 1;
		} else {
			auto directive = TableManager::GetDirective(dto.Operacao);
			if (directive != nullptr) {
				positionCount += ExecuteDirective(dto.Operacao, directive); // IMPLEMENTAR
			} else {
				ErrorPrinter::ShowError(ErrorType::Syntatic, outputFileName, lineCount, "Operacao" + dto.Operacao + "nao identificada");
			}
		}

		lineCount++;
	}
}
