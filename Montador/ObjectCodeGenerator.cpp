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
			code << "mov DWORD [" << arguments[0].SymbolName << "], ebx\n";
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
			code << "mov [" << arguments[0].SymbolName << "], ebx\n";
			break;
		case OpCodes::C_OUTPUT:
			code << "mov eax, [" << arguments[0].SymbolName << "]\n";
			code << "call escreverChar\n";
			break;
		case OpCodes::S_INPUT:
			code << "call lerString\n";
			code << "mov [" << arguments[0].SymbolName << "], ebx\n" ;
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
			bssSection << label << " resd " << vlr << "\n";
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
	WriteConstantData(file);

	if (dataSection.rdbuf()->in_avail()) {
		file << dataSection.str().c_str();
		file << "\n";
	}

	file << "section .text\n"
		 << "global _start\n"
		 << "_start:\n";

	file << code.str().c_str();
	WriteConstantText(file);
}

void ObjectCodeGenerator::WriteConstantData(fstream& file) {
	file << "char\tdb 0\naux \tdb 0\ntam_char equ $-char\nbuffer\t\ttimes 100 db 0\ntambuffer   equ 100\nmsg_erro\tdb 'Segmentation fault', 0x0d, 0x0a\nmsg_erroNumber\tdb 'Unkown Number', 0x0d, 0x0a\nnegSymbol\tdb '-'\ntam_negSymbol equ $-negSymbol\ntam_m_erro\tequ $-msg_erro\ntam_m_erroNumber\tequ $-msg_erroNumber\n";
}

void ObjectCodeGenerator::WriteConstantText(fstream& file) {
	file << "lerHex:\t\n\t\tmov eax, 3\n\t\tmov ebx, 0\n\t\tmov ecx, buffer\n\t\tmov edx, tambuffer\n\t\tint 0x80\n\t\tmov esi, 0\n\t\tmov eax, 0\n\t\tmov ebx, 0\n"
		"converteHex:\t\n\t\tmov BYTE bl, [buffer+esi]\n\t\tcmp bl, 0xA\n\t\tje GetBarraN_Hex\n\t\tcmp bl,0x30\n\t\tjb lancarErroNumber\n\t\tsub bl, 0x30 \n\t\tcmp bl,0xA\n\t\tjae verifyChar\n\t\t"
		"calculaHex:mov edx, 0x10\n\t\tmul edx\n\t\tmovzx edx, bl\n\t\tadd eax, edx\n\t\tinc esi\n\t\tmov ebx, 0\n\t\tjmp converteHex\n\t\t"
		"GetBarraN_Hex:\n\t\tmov ebx,[aux]\n\t\tcmp byte [aux],0x2D\n\t\tjne numeroPositivoHex\n\t\tneg eax\n\t\tnumeroPositivoHex:\n\t\tmov ebx,eax\n\t\tmov eax,esi\n\t\tret\n\t\tverifyChar:\n\t\tsub bl,0x7\n\t\tcmp bl,0X9\n\t\tjb lancarErroNumber\n\t\tcmp bl,0X10\n\t\tjae lancarErroNumber\n\t\tjmp calculaHex\n\n"
		"escreverHex:\n\t\tcmp eax,0x0\n\t\tjge maiorZeroHex\n\t\tneg eax\n\t\tmov [aux],eax\n \t\tmov eax, 4\n\t\tmov ebx, 1\n\t\tmov ecx,negSymbol\n\t\tmov edx, tam_negSymbol\n\t\tint 0x80\n\t\tmov eax,[aux] \t\n\t\tmaiorZeroHex:\n\t\tmov edx, 0\n\t\tmov ebx, 0X10\n\t\tdiv ebx\n\t\tcmp edx,0xA\n\t\tjb NaoEhChar\n\t\tadd edx,0x7\n\t\tNaoEhChar:add edx,0X30\n\t\t"
		"mov [buffer+esi], edx\n\t\tinc esi\n\t\tcmp DWORD eax, 0\n\t\tje fimBufferHex\n\t\tjmp escreverHex\n\t\tfimBufferHex:\n\t\tpush esi\n\t\tfimBufferHex2:\tmov eax, 4\n\t\tmov ebx, 1\n\t\tlea ecx, [buffer+esi]\n\t\tmov edx, 1\n\t\tint 0X80\n\t\tdec esi\n\t\tcmp esi, 0\n\t\tjge fimBufferHex2\n\t\tpop esi\n\t\tmov eax,esi\n\t\tret\n\n\n\nlerInteiro:\t\n\t\t"
		"mov eax, 3\n\t\tmov ebx, 0\n\t\tmov ecx, buffer\n\t\tmov edx, tambuffer\n\t\tint 0x80\n\t\tmov esi, 0\n\t\tmov eax, 0\n\t\tmov ebx, 0\nconverteNum:\t\n\t\tmov BYTE bl, [buffer+esi]\n\t\tcmp bl,0x2D\n\t\tjne ehPositivo\n\t\tmov byte [aux],bl\n\t\tinc esi\n\t\tmov ebx, 0\n\t\tjmp converteNum\n\t\tehPositivo:cmp bl, 0xA\n\t\tje GetBarraN\n\t\tcmp bl,0x30\n\t\tjb "
		"lancarErroNumber\n\t\tcmp bl,0x3A\n\t\tja lancarErroNumber\n\t\tsub bl, 0x30 \n\t\tmov edx, 0xA\n\t\tmul edx\n\t\tmovzx edx, bl\n\t\tadd eax, edx\n\t\tinc esi\n\t\tmov ebx, 0\n\t\tjmp converteNum\n\t\tGetBarraN:\n\t\tmov ebx,[aux]\n\t\tcmp byte [aux],0x2D\n\t\tjne numeroPositivo\n\t\tneg eax\n\t\tnumeroPositivo:\n\t\tmov ebx,eax\n\t\tmov eax,esi\n\t\tret\n\n"
		"escreverInteiro:\n\t\tcmp eax,0x0\n\t\tjge maiorZero\n\t\tneg eax\n\t\tmov [aux],eax\n \t\tmov eax, 4\n\t\tmov ebx, 1\n\t\tmov ecx,negSymbol\n\t\tmov edx, tam_negSymbol\n\t\tint 0x80\n\t\tmov eax,[aux]\n\t\tmaiorZero:mov edx, 0\n\t\tmov ebx, 0XA\n\t\tdiv ebx\n\t\tadd edx, 0X30\n\t\tmov [buffer+esi], edx\n\t\tinc esi\n\t\tcmp DWORD eax, 0\n\t\tje fimBuffer\n\t\tjmp "
		"escreverInteiro\n\t\tfimBuffer:\t\n\t\tpush esi\n\t\tfimBuffer2:\tmov eax, 4\n\t\tmov ebx, 1\n\t\tlea ecx, [buffer+esi]\n\t\tmov edx, 1\n\t\tint 0X80\n\t\tdec esi\n\t\tcmp esi, 0\n\t\tjge fimBuffer2\n\t\tpop esi\n\t\tmov eax,esi\n\t\tret\nlerChar:\t\n\t\tmov eax, 3\n\t\tmov ebx, 0\n\t\tmov ecx, char\n\t\tmov edx, tam_char\n\t\tint 0x80\n\t\tmov byte bl, [char]\n\t\t"
		"movzx eax, bl\n\t\tmov ebx,eax\n\t\tmov eax,0x1\n\t\tret\n\nescreverChar: \n\t\tmov eax, 4\n\t\tmov ebx, 1\n\t\tmov ecx, char\n\t\tmov edx, tam_char\n\t\tint 0x80\n\t\tmov eax,0x1\n\t\tret\n\n\nlerString:\t\n\t\tmov BYTE cl, 0x0\n\t\tmov esi, 0\n\t\tjmp resetaBuffer\n\t\tlacoLeitura:\tmov eax, 3\n\t\tmov ebx, 0\n\t\tmov ecx, buffer\n\t\tmov edx, tambuffer\n\t\tint 0x80\n\t\tmov esi, 99\n\t\tcmp BYTE [buffer+esi], 0x0\n\t\tje "
		"fimLeitura\n\t\tcmp BYTE [buffer+esi], 0xA\n\t\tje fimLeitura\n\t\tjmp lancarMsgErro\n\t\tfimLeitura:\n\t\tmov esi,0\n\t\tcontaCaracter:\n\t\tcmp BYTE [buffer+esi], 0xA\n\t\tinc esi\n\t\tje fim\n\t\tcmp BYTE [buffer+esi], 0x0\n\t\tje fim\n\t\tjmp contaCaracter\n\t\tfim:\n\t\tdec esi\n\t\tmov ebx,eax\n\t\tmov eax,esi\n\t\tret\n\t\tresetaBuffer: cmp BYTE cl, 100\n\t\tje lacoLeitura\n\t\t"
		"mov BYTE [buffer+esi], 0\n\t\tinc BYTE cl\n\t\tinc esi\n\t\tjmp resetaBuffer\n\t\tlancarMsgErro:\tmov eax, 4\n\t\tmov ebx, 1\n\t\tmov ecx, msg_erro\n\t\tmov edx, tam_m_erro\n\t\tint 0x80\n\t\tmov eax, 1\n\t\tmov ebx, 0\n\t\tint 0x80\n\t\t\nescreverString:\t\n\t\tmov BYTE bl, [buffer+esi]\n\t\tcmp bl , 0xA\n\t\tje fimEscrita\n\t\tmov eax, 4\n\t\tmov ebx, 1\n\t\tlea ecx, [buffer+esi]\n\t\tmov edx, 1\n\t\tint 0x80\n\t\tinc esi\n\t\t"
		"jmp escreverString\n\t\tfimEscrita:\tmov eax, 4\n\t\tmov ebx, 1\n\t\tlea ecx, [buffer+esi]\n\t\tmov edx, 1\n\t\tint 0x80\n\t\tmov eax,esi\n\t\tret\n\nlancarErroNumber: \n\t\tmov eax, 4\n\t\tmov ebx, 1\n\t\tmov ecx, msg_erroNumber\n\t\tmov edx, tam_m_erroNumber\n\t\tint 0x80\n\t\tmov eax, 1\n\t\tmov ebx, 0\n\t\tint 0x80\n\nlancarErro: \n\t\tmov eax, 4\n\t\tmov ebx, 1\n\t\tmov ecx, msg_erro\n\t\tmov edx, tam_m_erro\n\t\tint 0x80\n\t\t"
		"mov eax, 1\n\t\tmov ebx, 0\n\t\tint 0x80\n";
}
