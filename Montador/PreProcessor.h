#pragma once
#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <iostream>

using std::unordered_map;
using std::string;
using std::istream;
using std::fstream;

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
		fstream outputStream;

		void insertOnTable(string atributionLine);
		bool evaluate(string& ifExpression);
		string getNextLine(istream& stream);

};

