#include "ErrorPrinter.h"


void ErrorPrinter::ShowError(ErrorType type, string file, int lineNumber, string message) {
	string errorType;
	switch (type) {
		case ErrorPrinter::Lexic:
			errorType = "Lexico";
			break;
		case ErrorPrinter::Syntatic:
			errorType = "Sintatico";
			break;
		case ErrorPrinter::Semantic:
			errorType = "Semantico";
			break;
	}

	printf("Erro %s em %s(%d): %s\n", errorType.c_str(),file.c_str(),lineNumber,message.c_str());
}
