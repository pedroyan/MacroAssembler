#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "MacroAssemblerLibraries.h"

using std::string;


FILE* VerifyFile(const char* fileName);

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

	FILE* fp = VerifyFile(argv[2]);
	if (fp == nullptr) {
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

/// <summary>
/// Verifica a extensão do arquivo passado e se ele foi encontrado
/// </summary>
/// <param name="fileName">nome do arquivo</param>
/// <returns>Um ponteiro pro arquivo caso a verificação seja bem sucedida. Nullptr caso contrário</returns>
FILE* VerifyFile(const char* fileName) {
	string fileNameS(fileName);
	size_t extensionIndex = fileNameS.find_last_of(".");

	string extension = StringLibrary::ToLower(fileNameS.substr(extensionIndex + 1));

	if (extension != "asm") {
		printf("O Montador aceita somente arquivos .asm \nExtensao do arquivo passado: .%s\n", extension.c_str());
		return nullptr;
	}

	FILE* fp = fopen(fileName, "r");
	if (fp == nullptr) {
		printf("O arquivo especificado %s nao existe\n", fileName);
		return nullptr;
	}

	return fp;
}