#pragma once
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <vector>
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
	void Merge(string outputFile);
private:
	//string outputCode;
	vector<ModuleEngine> listOfModules;
	vector<int>listaFatoresCorerrecao;
	int numberOfModules=0;
	unordered_map<string, int > tableGlobalDefinition;
	float linkerHaveProblem=false;





};
