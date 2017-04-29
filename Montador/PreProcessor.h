#pragma once
#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

using std::unordered_map;
using std::string;
using std::istream;
using std::fstream;
using std::stringstream;

class PreProcessor {
	public:
		PreProcessor(string inputFileName, string outputFileName);
		~PreProcessor();
		/// <summary>
		/// Realiza o preprocessamento do arquivo passado
		/// </summary>
		/// <param name="stream">ponteiro para o arquivo a ser preprocessado</param>
		void PreProcessPass(istream& stream);
	private:
		unordered_map<string, int> valueTable;
		int lineCount;
		string inputFileName;
		string outputFileName;
		stringstream outputContent;

		void insertOnTable(string atributionLine);

		/// <summary>
		/// Avalia se a próxima linha deverá ser escrita ou não
		/// </summary>
		/// <param name="line">Linha lida da clausula IF. Será sobreescrita pela proxima linha</param>
		/// <param name="stream">stream de leitura</param>
		/// <returns>Flag indicando se a proxima linha vai ser escrita ou não</returns>
		bool evaluateIf(string& line, istream & stream);
		string getNextLine(istream& stream);
		void printError(string message);
		void saveFile();
		bool failed;

};

