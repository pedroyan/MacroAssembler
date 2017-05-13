#include "ErrorPrinter.h"


void ErrorPrinter::ShowError(ErrorType type, string file, int lineNumber, string message) {
	string errorType;
	switch (type) {
		case ErrorType::Lexic:
			errorType = "Lexico";
			break;
		case ErrorType::Syntatic:
			errorType = "Sintatico";
			break;
		case ErrorType::Semantic:
			errorType = "Semantico";
			break;
	}

	printf("Erro %s em %s(%d): %s\n", errorType.c_str(),file.c_str(),lineNumber,message.c_str());
}
