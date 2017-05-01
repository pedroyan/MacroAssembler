#pragma once
#include <list>
/*
#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>

using std::unordered_map;
using std::istream;
using std::fstream;
using std::stringstream;*/
using std::string;

class ObjectTable {
	public:
		ObjectTable(string variableName,int variableAdress);
		void SetCorrecao(int newAdress);
		int GetVariableAdress();
		string GetVariableName();
	private:
		string variableName;
		int variableAdress;

};

