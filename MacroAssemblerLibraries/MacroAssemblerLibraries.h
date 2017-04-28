#pragma once

#ifdef MACROASSEMBLERLIBRARIES_EXPORTS  
#define MACROASSEMBLERLIBRARIES __declspec(dllexport)   
#else  
#define MACROASSEMBLERLIBRARIES __declspec(dllimport)   
#endif 

#include <string>
#include <vector>
using std::string;
using std::vector;

class StringLibrary {
	public:

	/// <summary>
	/// Torna todas as letras de uma string em letras min�sculas
	/// </summary>
	/// <param name="originalCase">string original</param>
	/// <returns>string com letras min�sculas</returns>
	static MACROASSEMBLERLIBRARIES string ToLower(string originalCase);

	/// <summary>
	/// Torna todas as letras de uma string em letras min�sculas
	/// </summary>
	/// <param name="originalCase">string original</param>
	/// <returns>string com letras min�sculas</returns>
	static MACROASSEMBLERLIBRARIES string ToLower(char* originalCase);
	
	/// <summary>
	/// Remove todos os espa�os redundantes de uma string e tamb�m remove tabula��es
	/// substituindo-as por 1 espa�o.
	/// </summary>
	/// <param name="original">String a ser modificada</param>
	/// <returns>String sem tabula��es excessivas</returns>
	static MACROASSEMBLERLIBRARIES string RemoveExcessiveSpaces(string original);

	/// <summary>
	/// Divide a string pelo delimitador passado.
	/// 
	/// Implementada originalmente em: http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
	/// </summary>
	/// <param name="s">String a ser dividida</param>
	/// <param name="delim">Delimitador</param>
	/// <param name="v">Vetor onde ser�o inseridas as string divididas</param>
	static MACROASSEMBLERLIBRARIES void Split(const string &s, const char* delim, vector<string> &v);
};
