// MacroAssemblerLibraries.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MacroAssemblerLibraries.h"

string StringLibrary::ToLower(string originalCase) {
	string toReturn = originalCase;
	for (unsigned int i = 0; i < toReturn.length(); i++) {
		toReturn[i] = tolower(toReturn[i]);
	}
	return toReturn;
}

string StringLibrary::ToLower(char * originalCase) {
	string toReturn;
	for (unsigned int i = 0; i < strlen(originalCase); i++) {
		toReturn += tolower(originalCase[i]);
	}
	return toReturn;
}
