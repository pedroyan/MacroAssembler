#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "MacroAssemblerLibraries.h"

using std::string;

int main(int argc, char *argv[]) {

	#ifdef _DEBUG
	//seta programaticamente os argumentos em modo debug
	argv[1] = "-p";
	argv[2] = "assemblyTest.asm";
	#else
	//pega os argumentos da linha de comando em modo release
	if (argc < 4) {
		printf("Sao necessarios 3 argumentos para executar o montador:\n");
		printf("cmd>Montador <Tipo de Operacao> <Arquivo de Entrada> <Arquivo de Saida>\n");
		return 0;
	}
	#endif // DEBUG

	string tipoOperacao = StringLibrary::ToLower(argv[1]);

	FILE* fp = fopen(argv[2],"r");
	if (fp == nullptr) {
		printf("O arquivo especificado %s nao existe", argv[2]);
		return 0;
	}

	if (tipoOperacao == "-p") {
		printf("pre-processamento");
	} else if (tipoOperacao == "-o") {
		printf("montagem");
	} else {
		printf("tipo operação não especificado");
	}

	getchar();
	return 0;
}