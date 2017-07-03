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
	argv[1] = ".\\Triangulo.asm";
	argc = 2;
	#else
	//pega os argumentos da linha de comando em modo release
	if (argc != 2) {
		printf("Sao necessarios 1 argumento para executar o tradutor:\n");
		printf("cmd>Montador <Arquivo de Entrada>.asm \n");
		return 0;
	}
	#endif // DEBUG
	string inputName(argv[1]);
	auto initialIndex = inputName.find("\\");

	if (initialIndex != string::npos) {
		inputName = inputName.substr(initialIndex+1, inputName.size() - initialIndex -1);
	}

	string outputName = inputName.substr(0,inputName.find("."));

	ifstream fileStream;

	string message = "O Tradutor aceita somente arquivos .asm ";
	string allowedExtensions = "asm";

	message.append("e .pre ");
	allowedExtensions.append("|pre");

	if (FileLibrary::VerifyFile(argv[1],allowedExtensions.c_str(),message.c_str(),&fileStream)) {

		bool preSuccess = true;
		string inFile = argv[1];

		if (FileLibrary::GetFileExtension(argv[1]) == "asm") {
			PreProcessor processor(inputName.c_str(), outputName.c_str());
			preSuccess = processor.PreProcessPass(fileStream);
			inFile = outputName.c_str();
		}

		if (preSuccess) {
			Assembler assembler(inFile);
			if (assembler.Assemble()) {
				printf("%s.s gerado com sucesso\n", outputName.c_str());
			}
		}
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