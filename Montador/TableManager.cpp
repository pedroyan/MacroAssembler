#include "TableManager.h"


unordered_map<string, InstructionInfo> TableManager::InstructionTable{
	{"add", {1,1} },
	{"sub", {1,2} },
	{"mult",{1,3} },
	{"div", {1,4} },
	{"jmp", {1,5} },
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
	{"equ", {1,0}},
	{"if", {1,0}},
	{"public", {1,0}},
	{"extern", {0,0}},
	{"begin", {0,0}},
	{"end", {0,0}}
};

InstructionInfo * TableManager::GetInstruction(string name) {
	auto iterator = InstructionTable.find(name);
	if (iterator == InstructionTable.end()) {
		return nullptr;
	} else {
		return &iterator->second;
	}
}
