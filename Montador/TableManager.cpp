#include "TableManager.h"


unordered_map<string, InstructionInfo> TableManager::InstructionTable{
	{"add", {1,1} },
	{"sub", {1,2} },
};

InstructionInfo * TableManager::GetInstruction(string name) {
	auto iterator = InstructionTable.find(name);
	if (iterator == InstructionTable.end()) {
		return nullptr;
	} else {
		return &iterator->second;
	}
}
