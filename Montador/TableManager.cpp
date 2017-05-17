#include "TableManager.h"
#include <algorithm>

unordered_map<string, InstructionInfo> TableManager::InstructionTable{
	{"add", {1,OpCodes::ADD}},
	{"sub", {1,OpCodes::SUB}},
	{"mult",{1,OpCodes::MULT}},
	{"div", {1,OpCodes::DIV}},
	{"jmp", {1,OpCodes::JMP}},
	{"jmpn", {1,OpCodes::JMPN}},
	{"jmpp", {1,OpCodes::JMPP}},
	{"jmpz", {1,OpCodes::JMPZ}},
	{"copy", {2,OpCodes::COPY}},
	{"load", {1,OpCodes::LOAD}},
	{"store", {1,OpCodes::STORE}},
	{"input", {1,OpCodes::INPUT}},
	{"output", {1,OpCodes::OUTPUT}},
	{"stop", {0, OpCodes::STOP}}
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
vector<std::pair<string, int>> TableManager::UseTable;

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

void TableManager::InsertUse(string externalSymbolName, int address) {
	UseTable.push_back(std::make_pair(externalSymbolName, address));
}

struct Symbol {
	string name;
	SymbolInfo info;
};
bool sortByValor(const Symbol &lhs, const Symbol &rhs) { return lhs.info.address < rhs.info.address; }

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

vector<std::pair<string, int>>& TableManager::GetUseTable() {
	return UseTable;
}

void TableManager::Diagnostic_PrintSymbols() {
	vector<Symbol> vec;
	for (auto& x : SymbolTable) {
		vec.push_back({x.first,x.second});
	}
	std::sort(vec.begin(), vec.end(), sortByValor);

	printf("\n---------DIAGNOSTIC SYMBOL TABLE ----------\n");
	printf("Simb\tValor\textern");

	

	for (auto symbol : vec) {
		printf("\n%s\t%d\t%d",symbol.name.c_str(),symbol.info.address,symbol.info.externo);
	}
	printf("\n ----------------------------------------- \n");
}

bool sortByInt(const std::pair<string, int> &lhs, const std::pair<string, int> &rhs) { return lhs.second < rhs.second; }

void TableManager::Diagnostic_PrintDefinitions() {
	vector<std::pair<string, int>> vec;
	for (auto &it : DefinitionTable) {
		vec.push_back(std::make_pair(it.first, it.second));
	}
	std::sort(vec.begin(), vec.end(), sortByInt);

	printf("\n------DIAGNOSTIC DEFINITION TABLE --------\n");
	printf("Simb\tValor");

	for (auto symbol : vec) {
		printf("\n%s\t%d", symbol.first.c_str(), symbol.second);
	}

	printf("\n ----------------------------------------- \n");
}


