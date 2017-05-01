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

};

