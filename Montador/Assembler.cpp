#include "Assembler.h"


Assembler::Assembler(string outFileName) : scanner(outFileName,this) {
	outputFileName = outFileName;
	positionCount = 0;
	lineCount = 1;
}

Assembler::~Assembler() {
}

int Assembler::GetLine() {
	return lineCount;
}

void Assembler::Assemble() {
	while (scanner.CanRead()) {
		auto dto = scanner.GetNextTokens();
		lineCount++;
	}
}
