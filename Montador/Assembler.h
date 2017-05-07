#pragma once
#include<string>
#include"LexicalScanner.h"
#include "TableManager.h"

using std::string;

class Assembler {
	public:	
		Assembler(string outFileName);
		~Assembler();

		int GetLine();
		int ExecuteDirective(string directiveName, DirectiveInfo const * info);
		void Assemble();
	private:
		void firstPass();

		LexicalScanner scanner;
		string outputFileName;

		int positionCount;
		int lineCount;
		bool successAssemble;
};

