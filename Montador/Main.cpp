#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "StringLibrary.h"
#include "FileLibrary.h"
#include "PreProcessor.h"
#include "Assembler.h"

using std::string;
using std::ifstream;

ifstream VerifyFile(const char* fileName);

int main(int argc, char *argv[]) {

	#ifdef _DEBUG
	//seta programaticamente os argumentos em modo debug
	argv[1] = "-o";
	argv[2] = "fat_mod_A.asm";
	argv[3] = "middleFile";
	argc = 4;
	#else
	//pega os argumentos da linha de comando em modo release
	if (argc != 4) {
		printf("Sao necessarios 3 argumentos para executar o montador:\n");
		printf("cmd>Montador <Tipo de Operacao> <Arquivo de Entrada> <Arquivo de Saida>\n");
		return 0;
	}
	#endif // DEBUG
	string outputName(argv[3]);
	if (outputName.find(".") != string::npos) {
		printf("Nome do arquivo de saida nao pode conter extensao\n");
		return 0;
	}

	string tipoOperacao = StringLibrary::ToLower(argv[1]);

	ifstream fileStream;

	string message = "O Montador aceita somente arquivos .asm ";
	string allowedExtensions = "asm";

	if (tipoOperacao == "-p") {
		if (FileLibrary::VerifyFile(argv[2], allowedExtensions.c_str(), message.c_str(), &fileStream)) {
			PreProcessor processor(argv[2], argv[3]);
			if (processor.PreProcessPass(fileStream)) {
				printf("arquivo %s.pre gerado com sucesso\n", argv[3]);
			}
		}
	} else if (tipoOperacao == "-o") {
		message.append("e .pre ");
		allowedExtensions.append("|pre");

		if (FileLibrary::VerifyFile(argv[2],allowedExtensions.c_str(),message.c_str(),&fileStream)) {

			bool preSuccess = true;
			string inFile = argv[2];

			if (FileLibrary::GetFileExtension(argv[2]) == "asm") {
				PreProcessor processor(argv[2], argv[3]);
				preSuccess = processor.PreProcessPass(fileStream);
				inFile = argv[3];
			}

			if (preSuccess) {
				Assembler assembler(inFile);
				if (assembler.Assemble()) {
					printf("arquivo %s.o gerado com sucesso\n", argv[3]);
				}
			}
		}
	} else {
		printf("tipo de operacao nao especificada");
	}

	fileStream.close();
	printf("\nPressione enter para fechar");
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