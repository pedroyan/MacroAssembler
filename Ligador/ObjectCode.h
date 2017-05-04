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
		ObjectCode(int code);
		int GetCode();
		void SetCode(int newCode);
		void SetIsChanged(bool isChanged);
		bool GetIsChanged();


	private:
		int code;
		bool isChanged=false;
	
};

