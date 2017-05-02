#pragma once
/*
#include <stdio.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

using std::unordered_map;
using std::string;
using std::istream;
using std::fstream;
using std::stringstream;*/

class ObjectCode{
	public:
		ObjectCode(int address, int functionCode, int varAdress);
		int GetAddress();
		int GetFunctionCode();
		int GetVarAdress();


	private:
		int address;
		int functionCode;
		int varAdress;
		//bool para saber se deve passar o fator de correcao ou nao.se ele elstiver na tabela de uso nao passa o fator,se estiver passe o fator.lembrar de verificar se o numero eh >-1 pois numeros -1 nao devem ser inseridos no exe finals
};

