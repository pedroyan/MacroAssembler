#include "StringLibrary.h"
#include <regex>
#include <sstream>

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

 void StringLibrary::Tokenize(const string & s, const char * delim, vector<string>& v) {
	 // to avoid modifying original string
	 // first duplicate the original string and return a char pointer then free the memory
	 char * dup = _strdup(s.c_str());
	 char * token = strtok(dup, delim);
	 while (token != NULL) {
		 v.push_back(string(token));
		 // the call is treated as a subsequent calls to strtok:
		 // the function continues from where it left in previous invocation
		 token = strtok(NULL, delim);
	 }
	 free(dup);
}

 vector<string> StringLibrary::Tokenize(const string & s, const char * delim) {
	 vector<string> toReturn;
	 Tokenize(s, delim, toReturn);
	 return toReturn;
 }

 string StringLibrary::Trim(string s) {
	string whitespace = " \t";

	const auto strBegin = s.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = s.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return s.substr(strBegin, strRange);
 }

bool StringLibrary::IsInteger(string s) {

	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}
bool StringLibrary::IsHexadecimal(string s) {
	regex hexRegex("(\\+|-)?(0x)?([[:xdigit:]]+)");
	return std::regex_match(s,hexRegex);
}
int StringLibrary::ConvertHexaToInt(string s) {
	s = StringLibrary::ToLower(s);

	auto index = s.find("0x");
	auto negative = s.find("-") != string::npos;

	if (index != string::npos) {
		s = s.replace(0, index, "");
	}

	std::stringstream converter(s);
	int toReturn;
	converter >> std::hex >> toReturn;

	return negative ? -toReturn : toReturn;
}
bool StringLibrary::CompareInsensitive(string a, string b) {
	return ToLower(a) == ToLower(b);
}


