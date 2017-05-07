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
		int ExecuteDirective(string directiveName, DirectiveInfo const * info,vector<string> operands);
		void Assemble();
	private:
		void firstPass();

		LexicalScanner scanner;
		string outputFileName;

		int positionCount;
		int lineCount;
		bool successAssemble;
		unsigned char sectionFlags;
		enum SectionFlags {
			None = 0,
			Text = 1,
			Data = 2
		};


		void ShowError(string message, ErrorType type);
		int ExecuteSection(vector<string> operands);
		bool TryStringToInt(string s, int* result);
};

