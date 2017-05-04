#include "Leitor.h"
#include <vector>
#include <string>
#include "MacroAssemblerLibraries.h"


using std::vector;

void Leitor::ReadFile(ModuleEngine* module) { //recebe um ponteiro de arquivos e lê as informações para montar e preencher a matriz.
	string file = "arquivoTeste.o";// pasta debug da pasta do exe
	ifstream fp;
	fp.open(file);
	vector<string> members;
	vector<ObjectTable> tableUse,tableDefinition;
	vector<int> objectCode;
	auto line = GetNextLine(fp);
		if (line == string("TABLE USE")) {
			do {
				members.clear();
				line = GetNextLine(fp);
				StringLibrary::Tokenize(line, " ", members);
				if (members[0] != string("TABLE")) {
				tableUse.push_back(ObjectTable(members[0], atoi(members[1].c_str())));
				}

				
			} while (members[0] != string("TABLE"));
			module->SetTableUse(tableUse);
		}
		if (line == string("TABLE DEFINITION")) {
			do {
				members.clear();
				line = GetNextLine(fp);
				StringLibrary::Tokenize(line, " ", members);
				if (members[0] != string("TABLE")) {
					tableDefinition.push_back(ObjectTable(members[0], atoi(members[1].c_str())));
				}

			} while (members[0] != string("TABLE"));
			module->SetTableDefenition(tableDefinition);
		}
		if (line == string("TABLE REALOCATION")) {
			do {
				members.clear();
				line = GetNextLine(fp);
				StringLibrary::Tokenize(line, " ", members);
				if (members[0] != string("CODE")) {
					module->SetTableRealocation(members[0]);
				}

			} while (members[0] != string("CODE"));
		}
		if (line == string("CODE")) {
				members.clear();
				line = GetNextLine(fp);
				StringLibrary::Tokenize(line, " ", members);
				vector<int> codeObject;
				for(int i=0;i<members.size();i++){
					objectCode.push_back(atoi(members[i].c_str()));
				}
				module->SetListaObjectCode(objectCode);
				return;
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
string Leitor::GetNextLine(istream & stream) {
	string formatedLine;
	std::getline(stream, formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
}