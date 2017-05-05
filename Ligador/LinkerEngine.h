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

class LinkerEngine {//Classe que possui toda a logica de manipulacao dos modulos inseridos nela,assim os ligando corretamendo e informando se houve algum problema.
public:
	LinkerEngine();
	void AddModule(ModuleEngine module);
	/// <summary>
	/// Funcao que cria a tabela global de definicao.
	/// </summary>
	void ObtainGlobalDefinition();
	/// <summary>
	/// Funcao em que resolve todas as referencias cruzadas nos codigos objetos
	/// </summary>
	void ResolveReferencesCross();
	/// <summary>
	/// Funcao em que corrige os enderecos relativos dos codigos objetos
	/// </summary>
	void ResolveCorrecaoEnderecos();
	/// <summary>
	/// Funcao em que conecta os .o e assim cria o executavel.
	/// </summary>
	/// <param name="outputFile">Nome do arquivo .exe</param>
	void Merge(string outputFile);
	/// <summary>
	/// Funcao que procura na tabelaGlobal,o valor da variavel inserida.
	/// </summary>
	/// <param name="symbol">Entrada da tabela de Uso </param>
	/// <returns>Valor do endereco relativo</returns>
	int GetVarAdressGlobalTable(string symbol);
private:
	vector<ModuleEngine> listOfModules;
	vector<int>listaFatoresCorerrecao;
	int numberOfModules=0;
	unordered_map<string, int > tableGlobalDefinition;
	float linkerHaveProblem=false;





};
