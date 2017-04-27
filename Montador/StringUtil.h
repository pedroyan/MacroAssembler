#pragma once

#ifdef STRINGLIBRARY_EXPORTS  
#define STRINGLIBRARY_API __declspec(dllexport)   
#else  
#define STRINGLIBRARY_API __declspec(dllimport)   
#endif 

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

