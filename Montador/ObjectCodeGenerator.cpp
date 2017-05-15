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
	line = std::to_string(opCode);
	for (auto arg : arguments) {
		line +=  " " + std::to_string(arg.RealValue);
		if (arg.Extern) {
			tableRealocation << "0";
		} else {
			tableRealocation << "1";
		}
	}

	if(code.rdbuf() -> in_avail() == 0) {
		code << line;
	} else {
		code << " " + line;
	}
}

void ObjectCodeGenerator::WriteDirective(WrittenDirectivesType directive, int vlr) {
	switch (directive) {
		case WrittenDirectivesType::SPACE:
			for (size_t i = 0; i < vlr; i++) {
				code << " 00";
				tableRealocation << "0";
			}
			break;
		case WrittenDirectivesType::CONST:
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
		case GenerationType::Direct:
			file << code.rdbuf();
			break;
		case GenerationType::Modular:
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
	file << tableUse.str().c_str();
	file << "\nTABLE DEFINITION\n";
	file << tableDefinition.str().c_str();
	file << "\nTABLE REALOCATION\n";
	file << tableRealocation.str().c_str();
	file << "\n\nCODE\n";
	file << code.str().c_str();

}
