#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::stringstream;
using std::ifstream;
using std::string;
using std::vector;
using std::fstream;

struct ArgumentInfo {
	/// <summary>
	/// Flag indicando se o valor é externo
	/// </summary>
	bool Extern;

	/// <summary>
	/// Valor real de um operando (após operacoes de indice, caso houver)
	/// </summary>
	int RealValue;

	/// <summary>
	/// Nome do simbolo avaliado
	/// </summary>
	string SymbolName;

	ArgumentInfo(int realValue, bool isExtern) : Extern(isExtern), RealValue(realValue){}
};

enum class GenerationType {
	Direct,
	Modular
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
		/// Escreve uma instrucao no código objeto
		/// </summary>
		/// <param name="opCode">opcode da instrucao</param>
		/// <param name="arguments">argumentos da instrucao</param>
		void WriteInstruction(int opCode, const vector<ArgumentInfo>& arguments);

		/// <summary>
		/// Escreve uma diretiva no código objeto
		/// </summary>
		/// <param name="directive">Diretiva avaliada</param>
		/// <param name="vlr">Valor da diretiva</param>
		void WriteDirective(WrittenDirectivesType directive, int vlr);

		void GenerateFile(GenerationType type);

	private:
		GenerationType type;

		string outputFileName;
		stringstream code;
		stringstream tableDefinition;
		stringstream tableUse;
		stringstream tableRealocation;

		/// <summary>
		/// Escreve a tabela da definição
		/// </summary>
		void WriteTableDefinition();

		/// <summary>
		/// Escreve a tabela de uso
		/// </summary>
		void WriteTableUse();

		void GenerateModularFile(fstream& file);

};

