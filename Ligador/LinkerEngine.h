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
#include "ModuleEngine.h"
using std::cout;
using std::unordered_map;
using std::string;
using std::istream;
using std::fstream;
using std::stringstream;
using std::list;
using std::vector;

class LinkerEngine {
public:
	LinkerEngine();
	void AddModule(ModuleEngine module);
	void ObtainGlobalDefinition();
private:
	vector<ObjectCode> listaObjectCode;
	vector<ObjectTable> tableGlobalDefinition;
	vector<ModuleEngine> listOfModules;
	vector<int>correctionFactor;
	int numberOfModules=0;



};
