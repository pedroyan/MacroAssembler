#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "MacroAssemblerLibraries.h"

using std::string;

int main(int argc, char *argv[]) {
	if (argc < 4) {
		printf("Sao necessarios 3 argumentos para executar o montador:\n");
		printf("cmd>Montador <Tipo de Operacao> <Arquivo de Entrada> <Arquivo de Saida>\n");
		return 0;
	}
	string tipoOperacao = StringLibrary::ToLower(argv[1]);

	if (tipoOperacao == "-p") {
		printf("pre-processamento");
	} else if (tipoOperacao == "-o") {
		printf("montagem");
	} else {
		printf("tipo operação não especificado");
	}

	return 0;
}