#include "ObjectCode.h"

ObjectCode::ObjectCode(int code){
	this->code = code;
	
}



int ObjectCode::GetCode()
{
	return this->code;
}

void ObjectCode::SetIsChanged(bool isChanged){
	this->isChanged = isChanged;
}

bool ObjectCode::GetIsChanged()
{
	return this->isChanged;
}

void ObjectCode::SetCode(int newCode){
	this->code = newCode;

}
