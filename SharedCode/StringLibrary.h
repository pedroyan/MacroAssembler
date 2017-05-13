#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;
using std::istream;

class StringLibrary {
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
	
	/// <summary>
	/// Remove todos os espaços redundantes de uma string e também remove tabulações
	/// substituindo-as por 1 espaço.
	/// </summary>
	/// <param name="original">String a ser modificada</param>
	/// <returns>String sem tabulações excessivas</returns>
	static string RemoveExcessiveSpaces(string original);

	/// <summary>
	/// Divide a string pelos delimitadores passados.
	/// 
	/// Implementada originalmente em: http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
	/// </summary>
	/// <param name="s">String a ser dividida</param>
	/// <param name="delim">Delimitador</param>
	/// <param name="v">Vetor onde serão inseridas as string divididas</param>
	static void Tokenize(const string &s, const char* delim, vector<string> &v);

	/// <summary>
	/// Divide a string pelos delimitadores passados.
	/// 
	/// </summary>
	/// <param name="s">String a ser dividida</param>
	/// <param name="delim">Delimitador</param>
	/// <returns>Vetor com as strings dividadas</returns>
	static vector<string> Tokenize(const string &s, const char* delim);

	/// <summary>
	/// Remove todos os espaços em branco no começo e no fim de um string
	/// </summary>
	/// <param name="s">string que será reduzida</param>
	/// <returns>a string reduzida</returns>
	static string Trim(string s);

	/// <summary>
	/// Verifica se a string contém um número inteiro
	/// </summary>
	/// <param name="s">string a ser analisada</param>
	/// <returns>Uma flag indiciando se o número é inteiro</returns>
	static bool IsInteger(string s);

	/// <summary>
	/// Verifica se uma string contem um numero hexadecimal
	/// </summary>
	/// <param name="s">string a ser analisada</param>
	/// <returns>flag indicando se a string possui um numero hexadecimal</returns>
	static bool IsHexadecimal(string s);

	/// <summary>
	/// Converte uma string hexadecimal para um inteiro
	/// </summary>
	/// <param name="s">string a ser convertida</param>
	/// <returns>o inteiro convertido</returns>
	static int ConvertHexaToInt(string s);

	/// <summary>
	/// Compara string a com a string b sem considerar o case da letra
	/// </summary>
	/// <returns>True caso as strings sejam iguais</returns>
	static bool CompareInsensitive(string a, string b);
};
