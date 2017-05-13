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
		int ExecuteDirective(string directiveName, DirectiveInfo const * info,vector<string> operands, SymbolInfo* symbol);
		void Assemble();
	private:
		void firstPass();

		LexicalScanner scanner;
		string outputFileName;

		int positionCount;
		int lineCount;
		bool successAssemble;

		bool hasStop;

		unsigned char sectionFlags;
		enum SectionFlags {
			Text = 1,
			Data = 2
		};

		unsigned char beginFlags;
		enum BeginFlags {
			Begin = 1,
			End = 2
		};


		void ShowError(string message, ErrorType type);
		int ExecuteSection(vector<string> operands);
		bool TryStringToInt(string s, int* result);

		/// <summary>
		///	Preenche a tabela de definicoes com os valores dos simbolos publicos
		///	calculados na tabela de simbolos
		/// </summary>
		void setDefinitionTableValues();

		/*void CheckBeforeInsertingSymbol(string label, int position, bool isExtern);*/
};

