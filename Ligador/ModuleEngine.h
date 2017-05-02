#pragma once

#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <vector>
#include "ObjectTable.h"
#include "ObjectCode.h"

using std::vector;
using std::unordered_map;
using std::istream;
using std::fstream;
using std::stringstream;
using std::list;
using std::string;

class ModuleEngine {
public:
	ModuleEngine();
	void populateA();
	void populateB();
	vector<ObjectCode> GetListaObjectCode();
	vector<ObjectTable> GetGetTableUse();
	vector<ObjectTable> GetTableDefenition();
	void SetListaObjectCode(vector<ObjectCode> newObjectList);
	void SetGetTableUse(vector<ObjectTable> newTable);
	void SetTableDefenition(vector<ObjectTable> newTable);

private:
	vector<ObjectCode> listaObjectCode;
	vector<ObjectTable> tableUse;
	vector<ObjectTable> tableDefenition;
	//list<ObjectTable> tableRealocation;

};

