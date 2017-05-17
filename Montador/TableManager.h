#pragma once
#include <unordered_map>
#include <string>
#include <vector>

using std::unordered_map;
using std::string;
using std::vector;

enum class OpCodes {
	ADD = 1,
	SUB,
	MULT,
	DIV,
	JMP,
	JMPN,
	JMPP,
	JMPZ,
	COPY,
	LOAD,
	STORE,
	INPUT,
	OUTPUT,
	STOP
};

struct InstructionInfo {
	int operandCount;
	OpCodes opCode;
};

struct DirectiveInfo {
	/// <summary>
	/// -1 significa 0 ou 1;
	/// </summary>
	int operandCount;

	/// <summary>
	/// -1 significa tamanho vari�vel. 
	/// </summary>
	int size;
};

struct SymbolInfo {
	int address;
	bool externo;
	int spaceCount;

	SymbolInfo(int valor, bool ext) : address(valor), externo(ext), spaceCount(1) {};
};

class TableManager {
	public:
		/// <summary>
		/// Busca as informa��es de uma instrucao. Retorna Null caso n�o seja encontrada
		/// </summary>
		/// <param name="name">Nome da instrucao</param>
		/// <returns>As informacoes da instrucao caso ela seja encontrada.</returns>
		static InstructionInfo const * GetInstruction(string name);

		/// <summary>
		/// Busca as informa��es de uma diretiva. Retorna Null caso n�o seja encontrada
		/// </summary>
		/// <param name="directive">Nome da diretiva</param>
		/// <returns>Informa��es da diretiva</returns>
		static DirectiveInfo const * GetDirective(string directive);

		/// <summary>
		/// Busca as informacoes de um s�mbolo. Retorna null caso o simbolo n�o tenha sido encontrado
		/// </summary>
		/// <param name="symbol">simobolo procurado</param>
		/// <returns>informacoes de um s�mbolo</returns>
		static SymbolInfo * GetSymbol(string symbol);

		/// <summary>
		/// Insere um simbolo na tabela de simbolos
		/// </summary>
		/// <param name="symbolName">string que representa o simbolo</param>
		/// <param name="info">informacoes do simbolo</param>
		/// <returns>Informacoes do simbolo inserido</returns>
		static SymbolInfo* InsertSymbol(string symbolName, SymbolInfo info);

		/// <summary>
		/// Insere um simbolo na tabela de defini��o com o valor 0
		/// </summary>
		/// <param name="symbolName">Nome do simbolo a ser inserido</param>
		static void InsertDefinition(string symbolName);

		static void InsertUse(string externalSymbolName, int address);

		/// <summary>
		/// Busca o valor de um s�mbolo na tabela de defini��o. Retorna nullptr caso o simbolo
		/// n�o seja encontrado
		/// </summary>
		/// <param name="symbolName">Nome do simbolo procurado</param>
		/// <returns>Uma refer�ncia para o int que determina o valor do simbolo.</returns>
		static int* GetDefinitionValue(string symbolName);

		static unordered_map<string, int>& GetDefinitionTable();

		static vector<std::pair<string, int>>& GetUseTable();

		/// <summary>
		/// Imprime os simbolos na tabela de simbolos
		/// </summary>
		static void Diagnostic_PrintSymbols();

		/// <summary>
		/// Imprime a tabela de defini��es
		/// </summary>
		static void Diagnostic_PrintDefinitions();

	private:
		static unordered_map<string, InstructionInfo> InstructionTable;
		static unordered_map<string, DirectiveInfo> DirectiveTable;
		static unordered_map<string, SymbolInfo> SymbolTable;

		static unordered_map<string, int> DefinitionTable;
		static vector<std::pair<string, int>> UseTable;
};

