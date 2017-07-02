#include "ObjectCodeGenerator.h"

ObjectCodeGenerator::ObjectCodeGenerator(string objectFileName) {
	outputFileName = objectFileName.append(".s");
}

ObjectCodeGenerator::~ObjectCodeGenerator() {
}

void ObjectCodeGenerator::WriteInstruction(OpCodes opCode, const vector<ArgumentInfo>& arguments) {
	switch (opCode) {
		case OpCodes::ADD:
			code << "mov ebx, [" << arguments[0].SymbolName << "]\n";
			code << "add eax,ebx\n";
			break;
		case OpCodes::SUB:
			code << "mov ebx, [" << arguments[0].SymbolName << "]\n";
			code << "sub eax, ebx\n";
			break;
		case OpCodes::MULT:
			code << "mov ebx, [" << arguments[0].SymbolName << "]\n";
			code << "mul ebx\n";
			break;
		case OpCodes::DIV:
			code << "mov ebx, [" << arguments[0].SymbolName << "]\n";
			code << "div ebx" << "\n";
			break;
		case OpCodes::JMP:
			code << "jmp " << arguments[0].SymbolName << "\n";
			break;
		case OpCodes::JMPN:
			code << "js eax, " << arguments[0].SymbolName << "\n";
			break;
		case OpCodes::JMPP:
			code << "jns eax, " << arguments[0].SymbolName << "\n";
			break;
		case OpCodes::JMPZ:
			code << "cmp eax, 0\n";
			code << "je " << arguments[0].SymbolName << "\n";
			break;
		case OpCodes::COPY:
			code << "mov " << arguments[0].SymbolName << ", " << arguments[1].SymbolName << "\n";
			break;
		case OpCodes::LOAD:
			code << "mov eax, [" << arguments[0].SymbolName << "]\n";
			break;
		case OpCodes::STORE:
			code << "mov [" << arguments[0].SymbolName << "], eax\n";
			break;
		case OpCodes::INPUT:
			code << "call lerInteiro\n";
			code << "mov DWORD [" << arguments[0].SymbolName << "], eax\n";
			break;
		case OpCodes::OUTPUT:
			code << "mov eax, [" << arguments[0].SymbolName << "]\n";
			code << "mov esi, 0\n";
			code << "call escreverInteiro\n";
			break;
		case OpCodes::STOP:
			code << "mov eax, 1\n";
			code << "mov ebx, 0\n";
			code << "int 80h\n";
			break;
		case OpCodes::C_INPUT:
			code << "call lerChar\n";
			code << "mov [" << arguments[0].SymbolName << "], eax\n";
			break;
		case OpCodes::C_OUTPUT:
			code << "mov eax, [" << arguments[0].SymbolName << "]\n";
			code << "call escreverChar\n";
			break;
		case OpCodes::S_INPUT:
			code << "call lerString\n";
			code << "mov [" << arguments[0].SymbolName << "], eax\n" ;
			break;
		case OpCodes::S_OUTPUT:
			code << "mov eax, [" << arguments[0].SymbolName << "]\n";
			code << "mov esi, 0\n";
			code << "call escreverChar\n";
			break;
		default:
			break;
	}
}

void ObjectCodeGenerator::WriteDirective(WrittenDirectivesType directive, int vlr, string label) {
	switch (directive) {
		case WrittenDirectivesType::SPACE:
			bssSection << label << " resb " << vlr << "\n";
			break;
		case WrittenDirectivesType::CONST:
			dataSection << label << " dd " << vlr << "\n";
			break;
		default:
			break;
	}
}

void ObjectCodeGenerator::GenerateFile() {
	fstream file;
	file.open(outputFileName, std::fstream::out);
	GenerateModularFile(file);
	file.close();
}

void ObjectCodeGenerator::GenerateModularFile(fstream & file) {
	if (bssSection.rdbuf()->in_avail()) {
		file << "section .bss\n";
		file << bssSection.str().c_str();
		file << "\n";
	}

	file << "section .data\n";
	WriteConstantData();

	if (dataSection.rdbuf()->in_avail()) {
		file << dataSection.str().c_str();
		file << "\n";
	}

	file << "section .text\n"
		 << "global _start\n"
		 << "_start:\n";

	file << code.str().c_str();
}

void ObjectCodeGenerator::WriteConstantData() {
}
