#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "LinkerEngine.h"
#include "ModuleEngine.h"
#include "ObjectCode.h"
//#include "Leitor.h"
//#include "Leitor.h"
using std::cout;
using std::cin;
using std::advance;

using std::string;

int main(int argc, char *argv[]) {
	
	//Leitor testeLeitor;
	FILE *fp;
	string fileA = "arquivoTesteA.o";
	string fileB = "arquivoTesteB.o";
	//auto let = new Leitor;


	
	int pause;
	auto linker = new LinkerEngine;
	auto mod_A_teste = new ModuleEngine(fileA);
	linker->AddModule(*mod_A_teste);


	auto mod_B_teste = new ModuleEngine(fileB);
	linker->AddModule(*mod_B_teste);


	linker->Merge();

	cin >> pause;



	return 0;
}

	
