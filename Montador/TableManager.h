#pragma once
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

struct InstructionInfo {
	int operandCount;
	int opCode;
};

struct DirectiveInfo {
	/// <summary>
	/// -1 significa 0 ou 1;
	/// </summary>
	int operandCount;

	/// <summary>
	/// -1 significa tamanho vari�vel
	/// </summary>
	int size;
};

struct SymbolInfo {
	int vlr;
	bool externo;
	SymbolInfo(int valor, bool ext) : vlr(valor), externo(ext) {};
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
		static SymbolInfo* GetSymbol(string symbol);

		/// <summary>
		/// Insere um simbolo na tabela de simbolos
		/// </summary>
		/// <param name="symbolName">string que representa o simbolo</param>
		/// <param name="info">informacoes do simbolo</param>
		static void InsertSymbol(string symbolName, SymbolInfo info);

		/// <summary>
		/// Imprime os simbolos na tabela de simbolos
		/// </summary>
		static void Diagnostic_PrintSymbols();
	private:
		static unordered_map<string, InstructionInfo> InstructionTable;
		static unordered_map<string, DirectiveInfo> DirectiveTable;
		static unordered_map<string, SymbolInfo> SymbolTable;
};

