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
	auto mod_A_teste = new ModuleEngine;
	mod_A_teste->populateA();

	auto mod_B_teste = new ModuleEngine;
	mod_B_teste->populateB();
	auto teste = mod_A_teste->GetListaObjectCode();
	auto vat1 = teste[2];

	cout << vat1.GetFunctionCode();


	

	


	

	
	
	cin >> pause;

	return 0;
}

	
