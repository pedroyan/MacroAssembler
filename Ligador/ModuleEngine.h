#pragma once

#include <stdio.h>

#include <fstream>
#include <vector>
#include "ObjectTable.h"
#include "ObjectCode.h"

using std::vector;
using std::istream;
using std::string;

class ModuleEngine {
public:
	ModuleEngine(string fileName);
	vector<ObjectCode> GetListaObjectCode();
	vector<ObjectTable> GetTableUse();
	vector<ObjectTable> GetTableDefenition();
	vector<char> GetTableRealocation();
	void SetListaObjectCode(vector<ObjectCode> newObjectList);
	void SetTableUse(vector<ObjectTable> newTable);
	void SetTableDefenition(vector<ObjectTable> newTable);
	void SetTableRealocation(string newTable);
	void ReadFile();
	string GetNextLine(istream & stream);

private:
	vector<ObjectTable> tableUse;
	vector<ObjectTable> tableDefenition;
	vector<char> tableRealocation;
	vector<ObjectCode> listaObjectCode;
	string fileName;

};

