#pragma once
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <vector>
#include "ModuleEngine.h"
using std::cout;
using std::unordered_map;
using std::string;
using std::istream;
using std::fstream;
using std::stringstream;
using std::list;
using std::vector;

class LinkerEngine {//Possui toda a logica de manipulacao dos modulos inseridos nela,assim os ligando corretamendo e informando se houve algum problema.
public:
	LinkerEngine();
	void AddModule(ModuleEngine module);
	/// <summary>
	/// Cria a tabela global de definicao.
	/// </summary>
	void ObtainGlobalDefinition();
	/// <summary>
	/// Resolve todas as referencias cruzadas nos codigos objetos
	/// </summary>
	void ResolveReferencesCross();
	/// <summary>
	/// Corrige os enderecos relativos dos codigos objetos
	/// </summary>
	void ResolveCorrecaoEnderecos();
	/// <summary>
	/// Conecta os .o e assim cria o executavel.
	/// </summary>
	/// <param name="outputFile">Nome do arquivo .exe</param>
	void Merge(string outputFile);
	/// <summary>
	/// Procura na tabelaGlobal,o valor da variavel inserida.
	/// </summary>
	/// <param name="symbol">Entrada da tabela de Uso </param>
	/// <returns>Valor do endereco relativo</returns>
	int GetVarAdressGlobalTable(string symbol);
	/// <summary>
	/// Adiciona valores na GlobalTable e o ligador adicionar duas variaveis iguais.Resultando em erro de ligacao.
	/// </summary>
	/// <param name="nomeVariable">Nome da variavel inserida</param>
	/// <param name="adress">Valor de seu endereco</param>
	/// <returns>Retorna se houve algum erro de ligacao.</returns>
	bool AddVarAdressGlobalTable(string nomeVariable, int adress);
private:
	vector<ModuleEngine> listOfModules;
	vector<int>listaFatoresCorerrecao;
	int numberOfModules=0;
	unordered_map<string, int > tableGlobalDefinition;
	float linkerHaveProblem=false;





};
