#pragma once

#ifdef MACROASSEMBLERLIBRARIES_EXPORTS  
#define MACROASSEMBLERLIBRARIES __declspec(dllexport)   
#else  
#define MACROASSEMBLERLIBRARIES __declspec(dllimport)   
#endif 

#include <string>
using std::string;

class StringLibrary {
	public:

	/// <summary>
	/// Torna todas as letras de uma string em letras minúsculas
	/// </summary>
	/// <param name="originalCase">string original</param>
	/// <returns>string com letras minúsculas</returns>
	static MACROASSEMBLERLIBRARIES string ToLower(string originalCase);

	/// <summary>
	/// Torna todas as letras de uma string em letras minúsculas
	/// </summary>
	/// <param name="originalCase">string original</param>
	/// <returns>string com letras minúsculas</returns>
	static MACROASSEMBLERLIBRARIES string ToLower(char* originalCase);
};
