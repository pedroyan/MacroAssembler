#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "MacroAssemblerLibraries.h"
#include "FileLibrary.h"
#include "PreProcessor.h"
#include "LexicalScanner.h"

using std::string;
using std::ifstream;

ifstream VerifyFile(const char* fileName);

int main(int argc, char *argv[]) {

	#ifdef _DEBUG
	//seta programaticamente os argumentos em modo debug
	argv[1] = "-o";
	argv[2] = "assemblyTest.asm";
	argv[3] = "middleFile";
	#else
	//pega os argumentos da linha de comando em modo release
	if (argc < 4) {
		printf("Sao necessarios 3 argumentos para executar o montador:\n");
		printf("cmd>Montador <Tipo de Operacao> <Arquivo de Entrada> <Arquivo de Saida>\n");
		return 0;
	}
	#endif // DEBUG

	string tipoOperacao = StringLibrary::ToLower(argv[1]);

	ifstream fileStream;

	if (FileLibrary::VerifyFile(argv[2], "asm","O Montador aceita somente arquivos .asm ",&fileStream)) {
		if (tipoOperacao == "-p") {
			PreProcessor processor(argv[2], argv[3]);
			processor.PreProcessPass(fileStream);
		} else if (tipoOperacao == "-o") {
			PreProcessor processor(argv[2], argv[3]);
			if (processor.PreProcessPass(fileStream)) {
				LexicalScanner scanner(argv[3]);
				while (scanner.CanRead()) {
					auto oi = scanner.GetNextTokens();
				}				
			}
		} else {
			printf("tipo de operacao nao especificada");
		}
	}

	fileStream.close();
	printf("\nPressione enter para fechar");
	getchar();
	return 0;
}

/// <summary>
/// Verifica a extens�o do arquivo passado e se ele foi encontrado
/// </summary>
/// <param name="fileName">nome do arquivo</param>
/// <returns>Uma stream para o arquivo o caso a verifica��o seja bem sucedida. Sai do programa caso contrario</returns>
ifstream VerifyFile(const char* fileName) {
	string fileNameS(fileName);
	size_t extensionIndex = fileNameS.find_last_of(".");

	string extension = StringLibrary::ToLower(fileNameS.substr(extensionIndex + 1));

	if (extension != "asm") {
		printf("O Montador aceita somente arquivos .asm \nExtensao do arquivo passado: .%s\n", extension.c_str());
		exit(0);
	}

	ifstream file(fileName);
	if (!file.is_open()) {
		printf("O arquivo especificado %s nao existe\n", fileName);
		exit(0);
	}

	return file;
}