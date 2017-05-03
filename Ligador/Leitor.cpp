#include "Leitor.h"
#include <vector>
#include <string>

using std::vector;

void Leitor::MontaMatriz() { //recebe um ponteiro de arquivos e lê as informações para montar e preencher a matriz.
	vector<int> m;
	int teste;
	string aux;
	string file = "arquivoTeste.o";
	string table("TABLE");
	ifstream fp;
	fp.open(file);
	string verificaTable = RetiraString(fp);

	if (verificaTable== table) {
		do {
			verificaTable = RetiraString(fp);
			printf("%s ", verificaTable.c_str());
		} while (verificaTable != table);
	}

}

string Leitor::RetiraString(ifstream& fp) { // retira um numero do arquivo texto.
	int num, i;
	char c;
	vector<char> leitura;

	for (i = 0; i<50; i++) {
		fp.get(c);
		if (c == ' ' || c == '\n' ) {
			break;
		}
		leitura.push_back(c);
		
	}
	string saida(leitura.begin(), leitura.end());
	return saida;
}