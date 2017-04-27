#include <stdlib.h>
#include <stdio.h>
#include <string>

using std::string;

int main(int argc, char *argv[]) {
	if (argc < 4) {
		printf("Sao necessarios 3 argumentos para executar o montador:\n");
		printf("cmd>Montador <Tipo de Operacao> <Arquivo de Entrada> <Arquivo de Saida>\n");
	}
	string tipoOperacao(argv[1]);

	if (tipoOperacao == "-p") {

	}
	return 0;
}