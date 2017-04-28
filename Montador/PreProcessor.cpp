#include "PreProcessor.h"
#include "MacroAssemblerLibraries.h"
#include <sstream>
#include <regex>
#include <vector>

using std::vector;
using std::regex;
using std::regex_match;

regex equRegex("[^[:digit:]]([_[:alnum:]]+)?\\:([[:space:]]+)?EQU[[:space:]]([[:space:]]+)?([[:digit:]]+)([[:space:]]+)?");
regex ifRegex("IF[[:space:]]([[:space:]]+)?");
PreProcessor::PreProcessor(string inputFileName,string outputFileName) {
	lineCount = 1;
	string fileName = outputFileName + ".pre";
	outputStream.open(fileName, std::fstream::out);
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
}


PreProcessor::~PreProcessor() {
}

void PreProcessor::PreProcessPass(istream& stream) {
	string line;
	bool writeThisDown;
	while (stream.good()) {

		writeThisDown = true;
		line = getNextLine(stream);

		if (regex_match(line,equRegex)) {
			insertOnTable(line);
			writeThisDown = false;
		} else if (regex_match(line,ifRegex)) {

		}

		if (writeThisDown) {
			outputStream << line + "\n";
		}

		lineCount++;
	}
	outputStream.close();
	return;
}

void PreProcessor::insertOnTable(string atributionLine) {

	vector<string> stringDivision;

	StringLibrary::Split(atributionLine, ":", stringDivision);

	string identifier = stringDivision[0];

	if (valueTable.find(identifier) != valueTable.end()) {
		printf("Error %s(%d): Simbolo textual %s ja definido!", inputFileName.c_str(), lineCount,identifier.c_str());
		return;
	}

	string expression = stringDivision[1];

	stringDivision.clear();

	StringLibrary::Split(expression, " ", stringDivision);
	int valueNumber = std::stoi(stringDivision[1], nullptr);

	valueTable.emplace(std::make_pair(identifier, valueNumber));
}

bool PreProcessor::evaluate(string & ifExpression) {
	return false;
}

string PreProcessor::getNextLine(istream & stream) {
	string formatedLine;
	std::getline(stream, formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
}
