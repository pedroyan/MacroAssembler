#pragma once
#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "ErrorPrinter.h"

using std::unordered_map;
using std::string;
using std::ifstream;
using std::istream;
using std::fstream;
using std::stringstream;
using std::vector;

class PreProcessor {
	public:
		PreProcessor(string inputFileName, string outputFileName);
		~PreProcessor();
		/// <summary>
		/// Realiza o preprocessamento do arquivo passado
		/// </summary>
		/// <param name="stream">ponteiro para o arquivo a ser preprocessado</param>
		bool PreProcessPass(ifstream& stream);
	private:
		unordered_map<string, int> valueTable;
		int lineCount;
		bool preProcessingZone;

		string inputFileName;
		string outputFileName;
		stringstream outputContent;

		/// <summary>
		/// Avalia uma expressaoEQU
		/// </summary>
		/// <param name="equTokens"></param>
		void EvaluateEQU(const vector<string>& equTokens);

		bool IsEQU(vector<string> tokensLidos);

		/// <summary>
		/// Avalia se a pr�xima linha dever� ser escrita ou n�o
		/// </summary>
		/// <param name="line">Linha lida da clausula IF. Ser� sobreescrita pela proxima linha</param>
		/// <param name="stream">stream de leitura</param>
		/// <returns>Flag indicando se a proxima linha vai ser escrita ou n�o</returns>
		bool EvaluateIf(string& line, istream & stream);

		/// <summary>
		/// Pega a proxima linha da stream, j� removendo espa�os excessivos
		/// </summary>
		/// <param name="stream">stream sendo lida</param>
		/// <returns>Linha lida</returns>
		string getNextLine(istream& stream);

		/// <summary>
		/// Printa um erro com o nome do arquivo, a linha do erro e a mensagem
		/// </summary>
		/// <param name="message">mensagem a ser exibida</param>
		/// <param name="type">Tipo do erro</param>
		void printError(string message, ErrorType type);

		string transformEQU(string token);

		void saveFile();
		bool failed;

};

