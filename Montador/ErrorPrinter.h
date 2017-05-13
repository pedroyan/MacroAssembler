#pragma once
#include <string>

using std::string;

enum ErrorType { Lexic, Syntatic, Semantic };

class ErrorPrinter {
	public:

		/// <summary>
		/// Exibe um erro no console
		/// </summary>
		/// <param name="type">Tipo do erro</param>
		/// <param name="file">arquivo que ocorreu o erro</param>
		/// <param name="lineNumber">Linha em que ocorreu o erro</param>
		/// <param name="message">Mensagem de erro</param>
		static void ShowError(ErrorType type, string file, int lineNumber, string message);
};

