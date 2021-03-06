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
		/// flag indicando se a linha � vazia
		/// </summary>
		bool isEmpty;

		/// <summary>
		/// r�tulo, se houver
		/// </summary>
		string Rotulo;
		/// <summary>
		/// pode ser diretiva ou instrucao
		/// </summary>
		string Operacao;

		/// <summary>
		/// Operandos da Operacao
		/// </summary>
		vector<string> Operandos;
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
		/// Le a pr�xima linha e j� separa os tokens
		/// </summary>
		/// <returns>Tokens separados</returns>
		TokensDTO GetNextTokens();

		/// <summary>
		/// Volta a stream para o in�cio do arquivo
		/// </summary>
		void RestartStream();

		/// <summary>
		/// Remove os comentarios da linha passada
		/// </summary>
		static void RemoveComments(string & line);

		bool SuppressErrors;
	private:
		ifstream file;
		string getNextLine();
		Assembler* assembler;
		string fileName;
		ErrorType type;
		
		enum TokenType {
			Label,
			Operation,
			Operand
		};

		TokensDTO organizeTokens(vector<string> tokens);
		void ShowError(string message);
		bool validateToken(string token, TokenType operand);
		void throwError(string errorMessage, ErrorType type);
};

