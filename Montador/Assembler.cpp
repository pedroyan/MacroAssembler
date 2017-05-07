#include "Assembler.h"
#include "TableManager.h"
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
				ErrorPrinter::ShowError(ErrorPrinter::ErrorType::Syntatic, outputFileName, lineCount, "Simbolo " + dto.Rotulo + "redefinido");
			} else {
				TableManager::InsertSymbol(dto.Rotulo, positionCount);
			}
		}

		lineCount++;
	}
}
