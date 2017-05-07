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
		/// Busca a posicao de um s�mbolo. Retorna -1 caso o simbolo n�o tenha sido encontrado
		/// </summary>
		/// <param name="symbol">simobolo procurado</param>
		/// <returns>posicao de um s�mbolo</returns>
		static int GetSymbol(string symbol);

		/// <summary>
		/// Insere um simbolo na tabela de simbolos
		/// </summary>
		/// <param name="symbol">string que representa o simbolo</param>
		/// <param name="position">posi��o do simbolo</param>
		static void InsertSymbol(string symbol, int position);
	private:
		static unordered_map<string, InstructionInfo> InstructionTable;
		static unordered_map<string, DirectiveInfo> DirectiveTable;
		static unordered_map<string, int> SymbolTable;
};

