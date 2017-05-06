#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "ErrorPrinter.h"

using std::string;
using std::vector;
using std::ifstream;

class Assembler;

class TokensDTO {
	public:

		TokensDTO();

		/// <summary>
		/// flag indicando o sucesso da operacao
		/// </summary>
		bool success;

		/// <summary>
		/// rótulo, se houver
		/// </summary>
		string rotulo;
		/// <summary>
		/// pode ser diretiva ou instrucao
		/// </summary>
		string operacao;

		/// <summary>
		/// operandos da operacao
		/// </summary>
		vector<string> operandos;
};

class LexicalScanner {
	public:
		/// <summary>
		/// Inicializa o scanner lexico
		/// </summary>
		/// <param name="preFileName">Nome do arquivo .pre</param>
		LexicalScanner(string preFileName, Assembler* assembler);
		~LexicalScanner();

		/// <summary>
		/// Retorna se a stream pode continuar a ser lida
		/// </summary>
		/// <returns></returns>
		bool CanRead();

		/// <summary>
		/// Retorna o nome do arquivo
		/// </summary>
		string GetFileName();

		/// <summary>
		/// Le a próxima linha e já separa os tokens
		/// </summary>
		/// <returns>Tokens separados</returns>
		TokensDTO GetNextTokens();

		/// <summary>
		/// Remove os comentarios da linha passada
		/// </summary>
		static void RemoveComments(string & line);
	private:
		ifstream file;
		string getNextLine();
		Assembler* assembler;
		string fileName;

		TokensDTO organizeTokens(vector<string> tokens);
		void LexicalError(string message);
		bool validateToken(string token);

};

