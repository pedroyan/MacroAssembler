#include "FileLibrary.h"
#include "StringLibrary.h"

bool FileLibrary::VerifyFile(const char * fileName, string extensionsString, const char * extensionErrorMessage, ifstream* stream) {

	string fileExtension = StringLibrary::ToLower(GetFileExtension(fileName));
	auto extensions = StringLibrary::Tokenize(extensionsString, "|");

	auto foundExtension = std::find(extensions.begin(), extensions.end(), fileExtension);

	if (foundExtension == extensions.end()) {
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

string FileLibrary::JumpForNextLine(vector<string> members, ifstream & fp){
	string line;
	FileLibrary leitor;
		do {
			line = leitor.GetNextLine(fp);
			StringLibrary::Tokenize(line, " ", members);
		} while (members.size() == 0);
	

	return line;
}

string FileLibrary::GetFileExtension(string fileName) {
	size_t extensionIndex = fileName.find_last_of(".");
	if (extensionIndex == string::npos) {
		printf("O arquivo passado nao possui extensao. ");
		return false;
	}

	return fileName.substr(extensionIndex + 1);
}

