#include "ModuleEngine.h"
#include <fstream>
#include "StringLibrary.h"
#include "FileLibrary.h"
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

vector<string> ModuleEngine::GetFirstNonEmptyLine(ifstream & file) {
	vector<string> toReturn;
	string line;

	line = FileLibrary::GetNextLine(file);
	StringLibrary::Tokenize(line, " ", toReturn);
	if (toReturn.size() == 0) {
		line = FileLibrary::JumpForNextLine(toReturn, file);
		StringLibrary::Tokenize(line, " ", toReturn);
	}

	return toReturn;
}

void ModuleEngine::ReadFile() { // l� as informa��es  do aqruivo .o
	ifstream fp;

	fp.open(this->fileName);
	vector<string> members;
	vector<ObjectTable> tableUse, tableDefinition;
	vector<ObjectCode> objectCode;

	auto line = FileLibrary::GetNextLine(fp);
	StringLibrary::Tokenize(line, " ", members);

	if (StringLibrary::ToLower(members[1]) == string("use")) {
		do {
			members = GetFirstNonEmptyLine(fp);
			if (StringLibrary::ToLower(members[0]) != string("table")) {
				tableUse.push_back(ObjectTable(members[0], atoi(members[1].c_str())));
			}


		} while (StringLibrary::ToLower(members[0]) != string("table"));
		SetTableUse(tableUse);
	}

	StringLibrary::Tokenize(line, " ", members);
	if (StringLibrary::ToLower(members[1]) == string("definition")) {
		do {
			members = GetFirstNonEmptyLine(fp);
			if (StringLibrary::ToLower(members[0]) != string("table")) {
				tableDefinition.push_back(ObjectTable(members[0], atoi(members[1].c_str())));
			}

		} while (StringLibrary::ToLower(members[0]) != string("table"));
		 SetTableDefenition(tableDefinition);
	}
	StringLibrary::Tokenize(line, " ", members);
	if (StringLibrary::ToLower(members[1]) == string("realocation")) {
		do {
			members.clear();
			line = FileLibrary::GetNextLine(fp);
			StringLibrary::Tokenize(line, " ", members);
			if (members.size() == 0) {
				line = FileLibrary::JumpForNextLine(members, fp);
				StringLibrary::Tokenize(line, " ", members);
			}
			if (StringLibrary::ToLower(members[0]) != string("code")) {
				 SetTableRealocation(members[0]);
			}

		} while (StringLibrary::ToLower(members[0]) != string("code"));
	}

	if (StringLibrary::ToLower(line) == string("code")) {
		members.clear();
		line = FileLibrary::GetNextLine(fp);
		StringLibrary::Tokenize(line, " ", members);
		vector<int> codeObject;
		for (int i = 0; i<members.size(); i++) {
			objectCode.push_back(ObjectCode(atoi(members[i].c_str())));
		}
		 SetListaObjectCode(objectCode);
		return;
	}



}
