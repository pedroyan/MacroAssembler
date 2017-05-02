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
	
	/// <summary>
	/// Remove todos os espaços redundantes de uma string e também remove tabulações
	/// substituindo-as por 1 espaço.
	/// </summary>
	/// <param name="original">String a ser modificada</param>
	/// <returns>String sem tabulações excessivas</returns>
	static MACROASSEMBLERLIBRARIES string RemoveExcessiveSpaces(string original);

	/// <summary>
	/// Divide a string pelo delimitador passado.
	/// 
	/// Implementada originalmente em: http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
	/// </summary>
	/// <param name="s">String a ser dividida</param>
	/// <param name="delim">Delimitador</param>
	/// <param name="v">Vetor onde serão inseridas as string divididas</param>
	static MACROASSEMBLERLIBRARIES void Split(const string &s, const char* delim, vector<string> &v);

	/// <summary>
	/// Remove todos os espaços em branco no começo e no fim de um string
	/// </summary>
	/// <param name="s">string que será reduzida</param>
	/// <returns>a string reduzida</returns>
	static MACROASSEMBLERLIBRARIES string Trim(string s);

	/// <summary>
	/// Verifica se a string contém um número inteiro
	/// </summary>
	/// <param name="s">string a ser analisada</param>
	/// <returns>Uma flag indiciando se o número é inteiro</returns>
	static MACROASSEMBLERLIBRARIES bool IsInteger(string s);
};
