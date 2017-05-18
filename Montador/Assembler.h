#pragma once
#include<string>
#include <vector>
#include"LexicalScanner.h"
#include "TableManager.h"
#include "ObjectCodeGenerator.h"

using std::string;

class Assembler {
	public:	
		Assembler(string outFileName);
		~Assembler();

		int GetLine();
		int ExecuteDirective(string directiveName, DirectiveInfo const * info,vector<string> operands, SymbolInfo* symbol);
		bool Assemble();
	private:
		void firstPass();
		void secondPass();

		LexicalScanner scanner;
		ObjectCodeGenerator generator;

		int positionCount;
		int lineCount;
		bool successAssemble;
		

		bool hasStop;

		unsigned char sectionFlags;
		enum SectionFlags {
			Start = 0,
			Text = 1,
			Data = 2
		};

		unsigned char beginFlags;
		enum BeginFlags {
			Begin = 1,
			End = 2
		};
		enum operandTypes {
			number,
			label
		};
		/// <summary>
		/// Verifica se a diretiva se encontra na secao correta
		/// </summary>
		/// <param name="nomeDiretiva">String referente a diretiva para o programa indicar quando ela estiver errada</param>
		/// <param name="rigthSection">a secao correta em que a diretiva deve se encontrar</param>
		void CheckSection(string nomeDiretiva, unsigned char rigthSection);
		void ShowError(string message, ErrorType type);
		int ExecuteSection(vector<string> operands);
		bool TryStringToInt(string s, int* result);
		void FirstPassLastChecks();
		/// <summary>
		///	Preenche a tabela de definicoes com os valores dos simbolos publicos
		///	calculados na tabela de simbolos
		/// </summary>
		void setDefinitionTableValues();
		
		/// <summary>
		/// Checa se todos os operandos que possuem labels tenham as mesmas declaradas
		/// na tabela de simbolos
		/// </summary>
		/// <param name="operands">Operandos analisados</param>
		/// <returns>Uma flag booleana indicando se todas as labels foram declaradas</returns>
		bool CheckLabels(const vector<string>& operands);
		void ValidateAndWriteInstruction(const InstructionInfo* info, const vector<string>& operands);
		bool TryCalculateOperandRealValue(string operand, int& extractedValue, SymbolInfo** symbol, string& symbolName);

		/// <summary>
		/// Calcula o valor numerico do operando passado e faz checagem de indice de vetores
		/// com operador +
		/// </summary>
		/// <param name="operand"></param>
		/// <returns></returns>
		ArgumentInfo CalculateAndCheckArrayBoundaries(const string& operand);

		operandTypes GetType(string operand);
		bool evaluateDiv(const string& divOperand);

		void generateObjectFile();
};

