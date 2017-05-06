#include "FileLibrary.h"
#include "MacroAssemblerLibraries.h"

bool FileLibrary::VerifyFile(const char * fileName, const char * extension, const char * extensionErrorMessage, ifstream* stream) {
	string fileNameS(fileName);
	size_t extensionIndex = fileNameS.find_last_of(".");

	string fileExtension = StringLibrary::ToLower(fileNameS.substr(extensionIndex + 1));

	if (fileExtension != extension) {
		printf("%s \nExtensao do arquivo passado: .%s\n", extensionErrorMessage, fileExtension.c_str());
		return false;
	}

	stream->open(fileName, ifstream::in);
	if (!stream->is_open()) {
		printf("O arquivo especificado %s nao existe\n", fileName);
		return false;
	}

	return true;
}

string FileLibrary::GetNextLine(istream & stream){
	string formatedLine;
	std::getline(stream, formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
	
}
