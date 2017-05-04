#pragma once
#include <string>
using std::string;

class ObjectTable {
	public:
		ObjectTable(string variableName,int variableAdress);
		void AddFatorCorrecao(int newAdress);
		int GetVariableAdress();
		string GetVariableName();
	private:
		string variableName;
		int variableAdress;

};

