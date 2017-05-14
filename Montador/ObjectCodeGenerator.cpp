#include "ObjectCodeGenerator.h"
#include "TableManager.h"

ObjectCodeGenerator::ObjectCodeGenerator(string objectFileName) {
	outputFileName = objectFileName.append(".o");
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
				tableRealocation << "0";
			}
			break;
		case ObjectCodeGenerator::CONST:
			code << " "+std::to_string(vlr);
			tableRealocation << "0";
			break;
		default:
			break;
	}
}

void ObjectCodeGenerator::GenerateFile(GenerationType type) {
	fstream file;
	file.open(outputFileName, std::fstream::out);

	switch (type) {
		case ObjectCodeGenerator::Direct:
			file << code.rdbuf();
			break;
		case ObjectCodeGenerator::Modular:
			GenerateModularFile(file);
			break;
		default:
			break;
	}
	file.close();
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

void ObjectCodeGenerator::GenerateModularFile(fstream & file) {
	WriteTableDefinition();
	WriteTableUse();

	file << "TABLE USE\n";
	file << tableUse.rdbuf();
	file << "\nTABLE DEFINITION\n";
	file << tableDefinition.rdbuf();
	file << "\nTABLE REALOCATION\n";
	file << tableRealocation.rdbuf();
	file << "\nCODE\n";
	file << code.rdbuf();

}
