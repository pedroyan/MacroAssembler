#pragma once

#include <string>

using std::string;
class StringUtil {
	public:

		/// <summary>
		/// Torna todas as letras de uma string em letras min�sculas
		/// </summary>
		/// <param name="originalCase">string original</param>
		/// <returns>string com letras min�sculas</returns>
		static string ToLower(string originalCase);

		/// <summary>
		/// Torna todas as letras de uma string em letras min�sculas
		/// </summary>
		/// <param name="originalCase">string original</param>
		/// <returns>string com letras min�sculas</returns>
		static string ToLower(char* originalCase);
};

