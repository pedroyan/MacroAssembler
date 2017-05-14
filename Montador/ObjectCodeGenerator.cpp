#include "ObjectCodeGenerator.h"
#include "TableManager.h"

ObjectCodeGenerator::ObjectCodeGenerator(string objectFileName) {
	outputFileName = objectFileName;
}

ObjectCodeGenerator::~ObjectCodeGenerator() {
}

void ObjectCodeGenerator::WriteInstruction(int opCode, const vector<ArgumentInfo>& arguments) {
	string line = "";
	tableRealocation << "0"; //do opcode

	for (auto arg : arguments) {
		line += line.empty() ? std::to_string(arg.RealValue) : " " + std::to_string(arg.RealValue);
		tableRealocation << arg.Extern ? "0" : "1";
	}

	if(code.rdbuf() -> in_avail() == 0) {
		code << line;
	} else {
		code << " " + line;
	}
}

void ObjectCodeGenerator::WriteDirective(WrittenDirectivesType directive, int vlr) {
	switch (directive) {
		case ObjectCodeGenerator::SPACE:
			for (size_t i = 0; i < vlr; i++) {
				code << " 00";
			}
			break;
		case ObjectCodeGenerator::CONST:
			code << " "+std::to_string(vlr);
			break;
		default:
			break;
	}
}

void ObjectCodeGenerator::WriteTableDefinition() {
	const auto& defTable = TableManager::GetDefinitionTable();
	for (auto definition : defTable) {
		tableUse << definition.first + " " + std::to_string(definition.second) + "\n";
	}
}

void ObjectCodeGenerator::WriteTableUse() {
	const auto& useTable = TableManager::GetUseTable();
	for (auto use : useTable) {
		tableDefinition << use.first + " " + std::to_string(use.second) + "\n";
	}
}
