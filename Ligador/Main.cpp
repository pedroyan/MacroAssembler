#include <stdio.h>
#include <fstream>
#include "MacroAssemblerLibraries.h"
#include <stdlib.h>
#include <string>
#include "LinkerEngine.h"
#include "ModuleEngine.h"
#include "ObjectCode.h"
using std::cout;
using std::cin;
using std::advance;
using std::string;
using std::ifstream;
ifstream VerifyFile(const char* fileName);


int main(int argc, char *argv[]) {
#ifdef _DEBUG
	//seta programaticamente os argumentos em modo debug
	argv[1] = "arquivoTesteA.o";
	argv[2] = "arquivoTesteB.o";
	argv[3] = "arquivoTesteA.o";
	argv[4] = "arquivoTeste.e";
#else
	//pega os argumentos da linha de comando em modo release
	if (argc > 5 || argc < 4) {
		printf("Selecione ate 3 arquivos objetos para o ligador,juntamente com o arquivo .e ligador:\n");
		printf("cmd>Ligador <Arquivo de Entrada1> <Arquivo de Entrada2><Arquivo de Entrada3> <Arquivo de Saida>\n");
		return 1;
	}
#endif // DEBUG
	for (int i = 1; i < argc-1 ; i++) {//confere todos os arquivos .o se estao no formato correto
		ifstream& fileStream = VerifyFile(argv[i]);
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

/// <summary>
/// Verifica a extensão do arquivo passado e se ele foi encontrado
/// </summary>
/// <param name="fileName">nome do arquivo</param>
/// <returns>Uma stream para o arquivo o caso a verificação seja bem sucedida. Sai do programa caso contrario</returns>
ifstream VerifyFile(const char* fileName) {
	string fileNameS(fileName);
	size_t extensionIndex = fileNameS.find_last_of(".");

	string extension = StringLibrary::ToLower(fileNameS.substr(extensionIndex + 1));

	if (extension != "o") {
		printf("O ligador aceita somente arquivos .o para a leitura \nExtensao do arquivo passado: .%s\n", extension.c_str());
		exit(0);
	}

	ifstream file(fileName);
	if (!file.is_open()) {
		printf("O arquivo especificado %s nao existe\n", fileName);
		exit(0);
	}

	return file;
}