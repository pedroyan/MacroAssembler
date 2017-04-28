#include "PreProcessor.h"
#include "MacroAssemblerLibraries.h"
#include <sstream>
#include <regex>
using std::regex;
using std::regex_match;

regex equRegex("[^[:digit:]]([_[:alnum:]]+)\\:([[:space:]]+)?EQU[[:space:]]([[:space:]]+)?([[:digit:]]+)([[:space:]]+)?");
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
			insertOnTable(line);
		}
	}
	return;
}

void PreProcessor::insertOnTable(string atributionLine) {
	string cleanLine = StringLibrary::RemoveExcessiveSpaces(atributionLine);

}
