#include "TableManager.h"
#include <vector>
#include <algorithm>

using std::vector;

unordered_map<string, InstructionInfo> TableManager::InstructionTable{
	{"add", {1,1}},
	{"sub", {1,2}},
	{"mult",{1,3}},
	{"div", {1,4}},
	{"jmp", {1,5}},
	{"jmpn", {1,6}},
	{"jmpp", {1,7}},
	{"jmpz", {1,8}},
	{"copy", {2,9}},
	{"load", {1,10}},
	{"store", {1,11}},
	{"input", {1,12}},
	{"output", {1,13}},
	{"stop", {0, 14}}
};

unordered_map<string, DirectiveInfo> TableManager::DirectiveTable{
	{"section", {1,0}},
	{"space", {-1,-1}},
	{"const" , {1,1}},
	{"public", {1,0}},
	{"extern", {0,0}},
	{"begin", {0,0}},
	{"end", {0,0}}
};

unordered_map<string, SymbolInfo> TableManager::SymbolTable;
unordered_map<string, int> TableManager::DefinitionTable;
unordered_map<string, int> TableManager::UseTable;

InstructionInfo const * TableManager::GetInstruction(string name) {
	auto iterator = InstructionTable.find(name);
	if (iterator == InstructionTable.end()) {
		return nullptr;
	} else {
		return &iterator->second;
	}
}

DirectiveInfo const * TableManager::GetDirective(string directive) {
	auto iterator = DirectiveTable.find(directive);
	if (iterator == DirectiveTable.end()) {
		return nullptr;
	} else {
		return &iterator->second;
	}
}

SymbolInfo * TableManager::GetSymbol(string symbol) {
	auto iterator = SymbolTable.find(symbol);
	if (iterator == SymbolTable.end()) {
		return nullptr;
	} else {
		return &iterator->second;
	}
}

SymbolInfo * TableManager::InsertSymbol(string symbolName, SymbolInfo info) {
	SymbolTable.insert(std::make_pair(symbolName, info));
	return &SymbolTable.find(symbolName)->second;
}

void TableManager::InsertDefinition(string symbolName) {
	DefinitionTable.insert(std::make_pair(symbolName, 0));
}

struct Symbol {
	string name;
	SymbolInfo info;
};
bool sortByValor(const Symbol &lhs, const Symbol &rhs) { return lhs.info.vlr < rhs.info.vlr; }
//bool sortByName(const Person &lhs, const Person &rhs) { return lhs.name < rhs.name; }

int * TableManager::GetDefinitionValue(string symbolName) {
	auto iterator = DefinitionTable.find(symbolName);
	if (iterator == DefinitionTable.end()) {
		return nullptr;
	} else {
		return &iterator->second;
	}
}

unordered_map<string, int>& TableManager::GetDefinitionTable() {
	return DefinitionTable;
}

void TableManager::Diagnostic_PrintSymbols() {
	vector<Symbol> vec;
	for (auto& x : SymbolTable) {
		vec.push_back({x.first,x.second});
	}
	std::sort(vec.begin(), vec.end(), sortByValor);

	printf("\n---------DIAGNOSTIC SYMBOL TABLE -----------\n");
	printf("Simb\tValor\textern");

	

	for (auto symbol : vec) {
		printf("\n%s\t%d\t%d",symbol.name.c_str(),symbol.info.vlr,symbol.info.externo);
	}
	printf("\n ----------------------------------------- \n");
}


