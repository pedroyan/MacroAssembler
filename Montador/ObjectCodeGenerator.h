#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TableManager.h"

using std::stringstream;
using std::ifstream;
using std::string;
using std::vector;
using std::fstream;

struct ArgumentInfo {
	/// <summary>
	/// Flag indicando se o valor � externo
	/// </summary>
	bool Extern;

	/// <summary>
	/// Valor real de um operando (ap�s operacoes de indice, caso houver)
	/// </summary>
	int RealValue;

	/// <summary>
	/// Nome do simbolo avaliado
	/// </summary>
	string SymbolName;

	ArgumentInfo(int realValue, bool isExtern) : Extern(isExtern), RealValue(realValue){}
};

enum class WrittenDirectivesType {
	SPACE,
	CONST
};


class ObjectCodeGenerator {
	public:

		ObjectCodeGenerator(string objectFileName);
		~ObjectCodeGenerator();

		/// <summary>
		/// Escreve uma instrucao no c�digo objeto
		/// </summary>
		/// <param name="opCode">opcode da instrucao</param>
		/// <param name="arguments">argumentos da instrucao</param>
		void WriteInstruction(OpCodes opCode, const vector<ArgumentInfo>& arguments);

		/// <summary>
		/// Escreve uma diretiva no c�digo objeto
		/// </summary>
		/// <param name="directive">Diretiva avaliada</param>
		/// <param name="vlr">Valor da diretiva</param>
		void WriteDirective(WrittenDirectivesType directive, int vlr, string label);

		void GenerateFile();

	private:

		string outputFileName;
		stringstream code;
		stringstream dataSection;
		stringstream bssSection;

		void GenerateModularFile(fstream& file);
		void WriteConstantData(fstream& file);
		void WriteConstantText(fstream& file);

};

