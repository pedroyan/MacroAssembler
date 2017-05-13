#include <stdio.h>
#include <fstream>
#include "StringLibrary.h"
#include <stdlib.h>
#include <string>
#include "LinkerEngine.h"
#include "ModuleEngine.h"
#include "ObjectCode.h"
#include "FileLibrary.h"
using std::cout;
using std::cin;
using std::advance;
using std::string;
using std::ifstream;



int main(int argc, char *argv[]) {
#ifdef _DEBUG
	//seta programaticamente os argumentos em modo debug
	argv[1] = "arquivoTesteA.o";
	argv[2] = "arquivoTesteB.o";
	argv[3] = "arquivoTeste.e";
	argc = 4;
#else
	//pega os argumentos da linha de comando em modo release
	if (argc > 5 || argc < 4) {
		printf("Selecione entre 2 e 3 arquivos objetos e a saida\n");
		printf("cmd>Ligador <Arquivo de Entrada1> <Arquivo de Entrada2> (<Arquivo de Entrada3> opcional) <Arquivo de Saida>\n");
		return 1;
	}
#endif // DEBUG
	FileLibrary leitor;
	ifstream fileStream;
	for (int i = 1; i < argc-1 ; i++) {//confere todos os arquivos .o se estao no formato correto
		if (!leitor.VerifyFile(argv[i], "o", "O Ligador aceita somente arquivos .o para sua leitura", &fileStream)) {
			return 1;
		}
	}
	auto linker =  LinkerEngine();
	for (int  i = 1; i < argc-1 ; i++) {//adiciona todos os arquivos ao ligador
		auto File =  ModuleEngine(argv[i]);
		linker.AddModule(File);
	}
	
	linker.Merge(argv[argc-1]);
	getchar();
	return 0;
}
