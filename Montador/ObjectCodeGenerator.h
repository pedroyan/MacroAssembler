#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::stringstream;
using std::ifstream;
using std::string;
using std::vector;

struct ArgumentInfo {
	/// <summary>
	/// Flag indicando se o valor é externo
	/// </summary>
	bool Extern;

	/// <summary>
	/// Valor real de um operando (após operacoes de indice, caso houver)
	/// </summary>
	int RealValue;

	ArgumentInfo(int realValue, bool isExtern) : Extern(isExtern), RealValue(realValue){}
};

class ObjectCodeGenerator {
	public:
		enum GenerationType {
			Direct,
			Modular
		};

		enum WrittenDirectivesType {
			SPACE,
			CONST
		};


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

};

