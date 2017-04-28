#pragma once
#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <iostream>

using std::unordered_map;
using std::string;
using std::istream;

class PreProcessor {
	public:
		PreProcessor();
		~PreProcessor();
		/// <summary>
		/// Realiza o preprocessamento do arquivo passado
		/// </summary>
		/// <param name="stream">ponteiro para o arquivo a ser preprocessado</param>
		void PreProcessPass(istream& stream);
	private:
		unordered_map<string, int> ValueTable;
		void insertOnTable(string atributionLine);
};

