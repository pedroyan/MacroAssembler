#include "ObjectCode.h"

ObjectCode::ObjectCode(int address, int functionCode, int varAdress){
	this->address = address;
	this->functionCode = functionCode;
	this->varAdress = varAdress;
}

int ObjectCode::GetAddress()
{
	return this->address;
}

int ObjectCode::GetFunctionCode()
{
	return this->functionCode;
}

int ObjectCode::GetVarAdress()
{
	return this->varAdress;
}

void ObjectCode::SetIsChanged(bool isChanged){
	this->isChanged = isChanged;
}

bool ObjectCode::GetIsChanged()
{
	return this->isChanged;
}

void ObjectCode::SetVarAdress(int newAdress){
	this->varAdress = newAdress;

}
