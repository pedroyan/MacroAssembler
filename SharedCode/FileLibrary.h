#pragma once
#include <string>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::ifstream;
using std::istream;

class FileLibrary {
	public:
		/// <summary>
		/// Verifica a extensão do arquivo passado e se ele foi encontrado
		/// </summary>
		/// <param name="fileName">nome do arquivo</param>
		/// <param name="extension">Extensões esperadas do arquivo separadas por |</param>
		/// <param name="extensionErrorMessage">Mensagem de erro caso a extensão não seja encontrada</param>
		/// <returns>Uma stream para o arquivo o caso a verificação seja bem sucedida. Sai do programa caso contrario</returns>
		static bool VerifyFile(const char* fileName, string extension, const char* extensionErrorMessage, ifstream* stream);

		/// <summary>
		/// Le apenas uma linha de um arquivo 
		/// </summary>
		/// <param name="stream">Arquivo a ser lido</param>
		/// <returns>Linha lida</returns>
		static string GetNextLine(istream & stream);

		/// <summary>
		/// pula linhas em branco ate encontrar uma linha que contenha informacoes
		/// </summary>
		/// <param name="members">Contem a informacao contida na linha</param>
		/// <param name="fp">Arquivo sendo lido</param>
		/// <returns>Linha que possui informacoes</returns>
		static string JumpForNextLine(vector<string> members, ifstream & fp);

		/// <summary>
		/// Retorna a extensao do arquivo
		/// </summary>
		/// <param name="fileName">Nome do arquivo</param>
		static string GetFileExtension(string fileName);
		
	private:
		FileLibrary() {}
};

