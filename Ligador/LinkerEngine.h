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
	void ResolveReferencesCross();
	int GetVarAdressGlobalTable(string symbol);
	void ResolveCorrecaoEnderecos();
	void Merge();
private:
	//string outputCode;
	vector<ModuleEngine> listOfModules;
	vector<int>listaFatoresCorerrecao;
	int numberOfModules=0;
	unordered_map<string, int > tableGlobalDefinition;




};
