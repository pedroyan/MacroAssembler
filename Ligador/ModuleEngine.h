#pragma once

#include <stdio.h>

#include <fstream>
#include <vector>
#include "ObjectTable.h"
#include "ObjectCode.h"

using std::vector;
using std::istream;
using std::string;
using std::ifstream;

class ModuleEngine {//Possui todas as informacoes contidas no modulo lido pelo arquivo objeto
public:
	ModuleEngine(string fileName);
	void ReadFile();
	//string GetNextLine(istream & stream);
	vector<ObjectCode> GetListaObjectCode();
	vector<ObjectTable> GetTableUse();
	vector<ObjectTable> GetTableDefenition();
	vector<char> GetTableRealocation();
	void SetListaObjectCode(vector<ObjectCode> newObjectList);
	void SetTableUse(vector<ObjectTable> newTable);
	void SetTableDefenition(vector<ObjectTable> newTable);
	void SetTableRealocation(string newTable);

private:
	vector<ObjectTable> tableUse;
	vector<ObjectTable> tableDefenition;
	vector<char> tableRealocation;
	vector<ObjectCode> listaObjectCode;
	string fileName;
	vector<string> GetFirstNonEmptyLine(ifstream& file, string& lineBuffer);
	void FillObjectTable(vector<ObjectTable>& table, ifstream& file, string& lineBuffer);


};

