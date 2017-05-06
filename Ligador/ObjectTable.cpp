#include "ObjectTable.h"
ObjectTable::ObjectTable(string variableName, int variableAdress){
	this->variableAdress = variableAdress;
	this->variableName = variableName;
}

void ObjectTable::AddFatorCorrecao(int newAdress){
	this->variableAdress =this->variableAdress+newAdress;
}

int ObjectTable::GetVariableAdress()
{
	return this->variableAdress;
}

string ObjectTable::GetVariableName()
{
	return this->variableName ;
}
