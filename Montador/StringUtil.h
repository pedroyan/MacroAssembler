#pragma once

#include <string>

using std::string;
class StringUtil {
	public:

		/// <summary>
		/// Torna todas as letras de uma string em letras minúsculas
		/// </summary>
		/// <param name="originalCase">string original</param>
		/// <returns>string com letras minúsculas</returns>
		static string ToLower(string originalCase);

		/// <summary>
		/// Torna todas as letras de uma string em letras minúsculas
		/// </summary>
		/// <param name="originalCase">string original</param>
		/// <returns>string com letras minúsculas</returns>
		static string ToLower(char* originalCase);
};

