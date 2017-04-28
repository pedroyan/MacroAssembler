// MacroAssemblerLibraries.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MacroAssemblerLibraries.h"
#include <regex>

using std::regex;

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

string StringLibrary::RemoveExcessiveSpaces(string original) {
	regex lotsOfSpaces("(\\t|[[:space:]]([[:space:]]+))");
	return std::regex_replace(original, lotsOfSpaces, " ");
}

 void StringLibrary::Split(const string & s, const char * delim, vector<string>& v) {
	 // to avoid modifying original string
	 // first duplicate the original string and return a char pointer then free the memory
	 char * dup = strdup(s.c_str());
	 char * token = strtok(dup, delim);
	 while (token != NULL) {
		 v.push_back(string(token));
		 // the call is treated as a subsequent calls to strtok:
		 // the function continues from where it left in previous invocation
		 token = strtok(NULL, delim);
	 }
	 free(dup);
}
