#include "PreProcessor.h"
#include <sstream>
#include <regex>
using std::regex;
using std::regex_match;

regex equRegex("[^[:digit:]]([_[:alnum:]]+)([[:space:]]+)?\\:([[:space:]]+)?EQU[[:space:]]([[:space:]]+)?([[:digit:]]+)");
PreProcessor::PreProcessor() {
}


PreProcessor::~PreProcessor() {
}

void PreProcessor::PreProcessPass(istream& stream) {
	string line;
	int lineCount = 1;
	while (stream.good()) {
		std::getline(stream, line);
		if (regex_match(line,equRegex)) {
			printf("funcionou!");
		}
	}
	return;
}
