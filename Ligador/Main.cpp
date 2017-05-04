#include <stdlib.h>
#include <string>
#include "LinkerEngine.h"
#include "ModuleEngine.h"
#include "ObjectCode.h"
using std::cout;
using std::cin;
using std::advance;

using std::string;

int main(int argc, char *argv[]) {
	int pause;
	string fileA = "arquivoTesteA.o";
	string fileB = "arquivoTesteB.o";


	
	
	auto linker = new LinkerEngine;
	auto mod_A_teste = new ModuleEngine(fileA);
	linker->AddModule(*mod_A_teste);


	auto mod_B_teste = new ModuleEngine(fileB);
	linker->AddModule(*mod_B_teste);


	linker->Merge();

	cin >> pause;



	return 0;
}

	
