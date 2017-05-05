#pragma once
#include <string>
using std::string;

class ObjectTable {//classe das variaveis que ficam em tabelas de uso ou de definicao.
	public:
		ObjectTable(string variableName,int variableAdress);
		/// <summary>
		/// Acrecenta o valor de correcao ao endereco relativo.
		/// </summary>
		/// <param name="newAdress">Valor a ser adicionado para o endereco</param>
		void AddFatorCorrecao(int newAdress);
		int GetVariableAdress();
		string GetVariableName();
	private:
		string variableName;
		int variableAdress;

};

