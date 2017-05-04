#pragma once
#include <fstream>
#include <string>
#include <sstream>
using std::string;
using std::ifstream;
using std::istream;
#include "ModuleEngine.h"

class Leitor {
public:
	void ReadFile(ModuleEngine* module); //recebe um ponteiro de arquivos e lê as informações para montar e preencher a matriz.
	string RetiraString(ifstream &fp); // retira um numero do arquivo texto.
	string GetNextLine(istream & stream);
};