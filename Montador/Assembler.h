#pragma once
#include<string>
#include"LexicalScanner.h"
using std::string;

class Assembler {
	public:	
		Assembler(string outFileName);
		~Assembler();

		int GetLine();
		void Assemble();
	private:

		LexicalScanner scanner;
		string outputFileName;

		int positionCount;
		int lineCount;
};

