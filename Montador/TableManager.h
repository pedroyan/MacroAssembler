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
	/// -1 significa tamanho variável
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
		/// Busca as informações de uma instrucao. Retorna Null caso não seja encontrada
		/// </summary>
		/// <param name="name">Nome da instrucao</param>
		/// <returns>As informacoes da instrucao caso ela seja encontrada.</returns>
		static InstructionInfo const * GetInstruction(string name);

		/// <summary>
		/// Busca as informações de uma diretiva. Retorna Null caso não seja encontrada
		/// </summary>
		/// <param name="directive">Nome da diretiva</param>
		/// <returns>Informações da diretiva</returns>
		static DirectiveInfo const * GetDirective(string directive);

		/// <summary>
		/// Busca as informacoes de um símbolo. Retorna null caso o simbolo não tenha sido encontrado
		/// </summary>
		/// <param name="symbol">simobolo procurado</param>
		/// <returns>informacoes de um símbolo</returns>
		static SymbolInfo * GetSymbol(string symbol);

		/// <summary>
		/// Insere um simbolo na tabela de simbolos
		/// </summary>
		/// <param name="symbolName">string que representa o simbolo</param>
		/// <param name="info">informacoes do simbolo</param>
		/// <returns>Informacoes do simbolo inserido</returns>
		static SymbolInfo* InsertSymbol(string symbolName, SymbolInfo info);

		/// <summary>
		/// Insere um simbolo na tabela de definição com o valor 0
		/// </summary>
		/// <param name="symbolName">Nome do simbolo a ser inserido</param>
		static void InsertDefinition(string symbolName);

		/// <summary>
		/// Busca o valor de um símbolo na tabela de definição. Retorna nullptr caso o simbolo
		/// não seja encontrado
		/// </summary>
		/// <param name="symbolName">Nome do simbolo procurado</param>
		/// <returns>Uma referência para o int que determina o valor do simbolo.</returns>
		static int* GetDefinitionValue(string symbolName);

		static unordered_map<string, int>& GetDefinitionTable();

		/// <summary>
		/// Imprime os simbolos na tabela de simbolos
		/// </summary>
		static void Diagnostic_PrintSymbols();

		/// <summary>
		/// Imprime a tabela de definições
		/// </summary>
		static void Diagnostic_PrintDefinitions();
	private:
		static unordered_map<string, InstructionInfo> InstructionTable;
		static unordered_map<string, DirectiveInfo> DirectiveTable;
		static unordered_map<string, SymbolInfo> SymbolTable;

		static unordered_map<string, int> DefinitionTable;
		static unordered_map<string, int> UseTable;
};

