#include "ModuleEngine.h"
#include <fstream>
#include "MacroAssemblerLibraries.h"
using std::ifstream;


ModuleEngine::ModuleEngine(string fileName){
	this->fileName = fileName;
	ReadFile();
	
}

vector<ObjectCode> ModuleEngine::GetListaObjectCode(){
	return this->listaObjectCode;
}

vector<ObjectTable> ModuleEngine::GetTableUse(){
	return this->tableUse;
}

vector<ObjectTable> ModuleEngine::GetTableDefenition(){
	return this->tableDefenition;
}

vector<char> ModuleEngine::GetTableRealocation(){
	return this->tableRealocation;
}

void ModuleEngine::SetListaObjectCode(vector<ObjectCode> newObjectList){
	this->listaObjectCode.clear();
	this->listaObjectCode = newObjectList;
}

void ModuleEngine::SetTableUse(vector<ObjectTable> newTable){
	this->tableUse.clear();
	this->tableUse = newTable;
}

void ModuleEngine::SetTableDefenition(vector<ObjectTable> newTable){
	this->tableDefenition.clear();
	this->tableDefenition = newTable;
}

void ModuleEngine::SetTableRealocation(string newTable){
	vector<char> data(newTable.begin(), newTable.end());
	this->tableRealocation = data;

}
void ModuleEngine::ReadFile() { //recebe um ponteiro de arquivos e lê as informações 
	ifstream fp;
	fp.open(this->fileName);
	vector<string> members;
	vector<ObjectTable> tableUse, tableDefinition;
	vector<ObjectCode> objectCode;
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
		 SetTableUse(tableUse);
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
		 SetTableDefenition(tableDefinition);
	}
	if (line == string("TABLE REALOCATION")) {
		do {
			members.clear();
			line = GetNextLine(fp);
			StringLibrary::Tokenize(line, " ", members);
			if (members[0] != string("CODE")) {
				 SetTableRealocation(members[0]);
			}

		} while (members[0] != string("CODE"));
	}
	if (line == string("CODE")) {
		members.clear();
		line = GetNextLine(fp);
		StringLibrary::Tokenize(line, " ", members);
		vector<int> codeObject;
		for (int i = 0; i<members.size(); i++) {
			objectCode.push_back(ObjectCode(atoi(members[i].c_str())));
		}
		 SetListaObjectCode(objectCode);
		return;
	}



}

string ModuleEngine::GetNextLine(istream & stream) {
	string formatedLine;
	std::getline(stream, formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
}