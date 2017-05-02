#include <stdlib.h>
#include <stdio.h>
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
	auto linker = new LinkerEngine;
	auto mod_A_teste = new ModuleEngine;
	mod_A_teste->populateA();
	linker->AddModule(*mod_A_teste);

	auto mod_B_teste = new ModuleEngine;
	mod_B_teste->populateB();
	
	linker->AddModule(*mod_B_teste);
	linker->ObtainGlobalDefinition();
	linker->ResolveReferencesCross();
	
	cout << "fim";
	cin >> pause;



	return 0;
}

	
