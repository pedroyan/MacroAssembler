#include "Assembler.h"
#include "TableManager.h"

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
		if (dto.Rotulo == "" && dto.Operacao=="") {
			if (!dto.Done) {
				successAssemble = false;
			}
			continue;
		}

		auto info = TableManager::GetInstruction("sub");
		lineCount++;
	}
}
