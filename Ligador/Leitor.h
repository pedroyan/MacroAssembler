#pragma once
#include <fstream>
#include <string>

using std::string;
using std::ifstream;

class Leitor {
public:
	void MontaMatriz(); //recebe um ponteiro de arquivos e l� as informa��es para montar e preencher a matriz.
	string RetiraString(ifstream &fp); // retira um numero do arquivo texto.
};