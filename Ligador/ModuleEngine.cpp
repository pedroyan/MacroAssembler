#include "ModuleEngine.h"

ModuleEngine::ModuleEngine(){
	
}

void ModuleEngine::populateA(){
	//populando o codigo objeto
	/*this->listaObjectCode.push_back(ObjectCode(0, 12, 0));
	this->listaObjectCode.push_back(ObjectCode(2, 10, 11));
	this->listaObjectCode.push_back(ObjectCode(4, 1 , 0));
	this->listaObjectCode.push_back(ObjectCode(6, 11, 2));
	this->listaObjectCode.push_back(ObjectCode(8, 7, 0));
	this->listaObjectCode.push_back(ObjectCode(10, 14, -1));
	this->listaObjectCode.push_back(ObjectCode(11, 5, -1));*/

	//populando a tabela de uso 
	this->tableUse.push_back(ObjectTable("Y", 1));
	this->tableUse.push_back(ObjectTable("Y", 5));
	this->tableUse.push_back(ObjectTable("Y", 7));
	this->tableUse.push_back(ObjectTable("MOD_B", 9));

	//populando a tabela de definicao
	this->tableDefenition.push_back(ObjectTable("L1", 10));
	this->tableDefenition.push_back(ObjectTable("VAL", 11));

	//populando a tabela de realocacoa
	string initialValue("010101010100");
	vector<char> data(initialValue.begin(), initialValue.end());
	this->tableRealocation = data;
	//populando o codigo objeto2
	this->listaObjectCode.push_back(12);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(10);
	this->listaObjectCode.push_back(11);
	this->listaObjectCode.push_back(1);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(11);
	this->listaObjectCode.push_back(2);
	this->listaObjectCode.push_back(7);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(14);
	this->listaObjectCode.push_back(5);

	
}

void ModuleEngine::populateB(){
	//populando o codigo objeto
	/*this->listaObjectCode.push_back(ObjectCode(0, 13, 8));
	this->listaObjectCode.push_back(ObjectCode(2, 13, 0));
	this->listaObjectCode.push_back(ObjectCode(4, 13, 10));
	this->listaObjectCode.push_back(ObjectCode(6, 5 , 0));
	this->listaObjectCode.push_back(ObjectCode(8,-1, -1));
	this->listaObjectCode.push_back(ObjectCode(9,-1, -1));
	this->listaObjectCode.push_back(ObjectCode(10,-1, -1));*/

	//populando a tabela de uso 
	this->tableUse.push_back(  ObjectTable("VAL", 3));
	this->tableUse.push_back(  ObjectTable("L1", 7));
	

	//populando a tabela de definicao
	this->tableDefenition.push_back(  ObjectTable("MOD_B",0));
	this->tableDefenition.push_back(  ObjectTable("Y", 8));

	//populando a tabela de realocacoa
	string initialValue("01010101000");
	vector<char> data(initialValue.begin(), initialValue.end());
	this->tableRealocation = data;
	//populando o codigo objeto2
	this->listaObjectCode.push_back(13);
	this->listaObjectCode.push_back(8);
	this->listaObjectCode.push_back(13);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(13);
	this->listaObjectCode.push_back(10);
	this->listaObjectCode.push_back(5);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(0);
	this->listaObjectCode.push_back(0);
	
}

vector<int> ModuleEngine::GetListaObjectCode(){
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

void ModuleEngine::SetListaObjectCode(vector<int> newObjectList){
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


