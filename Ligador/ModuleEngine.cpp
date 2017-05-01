#include "ModuleEngine.h"

ModuleEngine::ModuleEngine(){
	
}

void ModuleEngine::populateA(){
	//populando o codigo objeto
	this->listaObjectCode.push_back(ObjectCode(0, 12, 0));
	this->listaObjectCode.push_back(ObjectCode(2, 10, 11));
	this->listaObjectCode.push_back(ObjectCode(4, 1 , 0));
	this->listaObjectCode.push_back(ObjectCode(6, 11, 2));
	this->listaObjectCode.push_back(ObjectCode(8, 7, 0));
	this->listaObjectCode.push_back(ObjectCode(10, 14, -1));
	this->listaObjectCode.push_back(ObjectCode(11, 5, -1));

	//populando a tabela de uso 
	this->tableUse.push_back(ObjectTable("Y", 1));
	this->tableUse.push_back(ObjectTable("Y", 5));
	this->tableUse.push_back(ObjectTable("Y", 7));
	this->tableUse.push_back(ObjectTable("MOD_B", 9));

	//populando a tabela de definicao
	this->tableDefenition.push_back(ObjectTable("L1", 10));
	this->tableDefenition.push_back(ObjectTable("VAL", 11));


	
}

void ModuleEngine::populateB(){
	//populando o codigo objeto
	this->listaObjectCode.push_back(ObjectCode(0, 13, 8));
	this->listaObjectCode.push_back(ObjectCode(2, 13, 0));
	this->listaObjectCode.push_back(ObjectCode(4, 13, 0));
	this->listaObjectCode.push_back(ObjectCode(6, 5 , 0));
	this->listaObjectCode.push_back(ObjectCode(8,-1, -1));
	this->listaObjectCode.push_back(ObjectCode(9,-1, -1));
	this->listaObjectCode.push_back(ObjectCode(10,-1, -1));

	//populando a tabela de uso 
	this->tableUse.push_back(  ObjectTable("VAL", 3));
	this->tableUse.push_back(  ObjectTable("L1", 7));
	

	//populando a tabela de definicao
	this->tableDefenition.push_back(  ObjectTable("MOD_B",0));
	this->tableDefenition.push_back(  ObjectTable("Y", 8));
}

vector<ObjectCode> ModuleEngine::GetListaObjectCode(){
	return this->listaObjectCode;
}

vector<ObjectTable> ModuleEngine::GetGetTableUse(){
	return this->tableUse;
}

vector<ObjectTable> ModuleEngine::GetTableDefenition(){
	return this->tableDefenition;
}
