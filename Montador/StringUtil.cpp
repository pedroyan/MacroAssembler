#include "StringUtil.h"

string StringUtil::ToLower(string originalCase) {
	string toReturn = originalCase;
	for (unsigned int i = 0; i < toReturn.length(); i++) {
		toReturn[i] = tolower(toReturn[i]);
	}
	return toReturn;
}

string StringUtil::ToLower(char * originalCase) {
	string toReturn;
	for (unsigned int i = 0; i < strlen(originalCase); i++) {
		toReturn += tolower(originalCase[i]);
	}
	return toReturn;
}
