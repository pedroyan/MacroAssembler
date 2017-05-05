#pragma once
#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class FileLibrary {
	public:
		/// <summary>
		/// Verifica a extens�o do arquivo passado e se ele foi encontrado
		/// </summary>
		/// <param name="fileName">nome do arquivo</param>
		/// <param name="extension">Extens�o esperada do arquivo</param>
		/// <param name="extensionErrorMessage">Mensagem de erro caso a extens�o n�o seja encontrada</param>
		/// <returns>Uma stream para o arquivo o caso a verifica��o seja bem sucedida. Sai do programa caso contrario</returns>
	static bool VerifyFile(const char* fileName, const char* extension, const char* extensionErrorMessage, ifstream* stream);
};

