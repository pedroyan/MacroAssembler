#include "LinkerEngine.h"
#include "ObjectTable.h"
#include "ObjectCode.h"
#include <sstream>

LinkerEngine::LinkerEngine(){
}

void LinkerEngine::AddModule(ModuleEngine  module){
	this->listOfModules.push_back(module);
	auto sizeCodigoObjeto=module.GetListaObjectCode().size();
	if (this->numberOfModules > 0) {//calcula o fator de correcao para o proximo modulo
		this->listaFatoresCorerrecao.push_back(module.GetListaObjectCode().size()  + listaFatoresCorerrecao[numberOfModules]);
		this->numberOfModules = this->numberOfModules + 1;
		return;
	}//calcula o fator de correcao para o proximo modulo caso nao tennha modulos anteriores
	this->listaFatoresCorerrecao.push_back(0);
	this->listaFatoresCorerrecao.push_back(module.GetListaObjectCode().size() );
	this->numberOfModules = this->numberOfModules + 1;
	
	
}

void LinkerEngine::ObtainGlobalDefinition() {//Funcao que obtem a juncao das tabelas de definicao,junto com as correcoes de endereco.Criando a tabela global de definicao.
	for (int i = 0; i < numberOfModules; i++) {
		auto listaDefinicao  = this->listOfModules[i].GetTableDefenition();
		for (int y = 0; y < listaDefinicao.size(); y++) {
			if (i > 0) {
				listaDefinicao[y].AddFatorCorrecao(this->listaFatoresCorerrecao[i]);
			}
			auto enderecoRelativo = listaDefinicao[y];
			this->tableGlobalDefinition.emplace(enderecoRelativo.GetVariableName(), enderecoRelativo.GetVariableAdress());

		}
	}
}

void LinkerEngine::ResolveReferencesCross(){//Funcao em que resolve todas as referencias cruzadas nos codigos objetos
	for (int i = 0; i < numberOfModules; i++) {
		//guarda a tabela de uso e codigoObjeto de cada modulo
		auto objectCode = this->listOfModules[i].GetListaObjectCode();
		auto tabelaUso = this->listOfModules[i].GetTableUse();
		if (!this->linkerHaveProblem) {
			for (int y = 0; y < tabelaUso.size(); y++) {
				//para cada modulo,analisa a tabela de uso e muda o endereco de seus dados
				auto enderecoParaAtulizar = tabelaUso[y].GetVariableAdress();
				auto newAdress = GetVarAdressGlobalTable(tabelaUso[y].GetVariableName());
				objectCode[enderecoParaAtulizar] = newAdress + objectCode[enderecoParaAtulizar].GetCode();
				objectCode[enderecoParaAtulizar].SetIsChanged(true);

			}
			this->listOfModules[i].SetListaObjectCode(objectCode);
		}
	}
}

int LinkerEngine::GetVarAdressGlobalTable(string symbol){//Funcao que retorna o valor da tabela de definicao global, retornando assim o valor da variavel inserida.
	auto map = this->tableGlobalDefinition.find(symbol);
	if (map == this->tableGlobalDefinition.end()) {//caso nao encotnre o valor na tabela,o codigo exe nao sera produzido e o terminal ira mostrar a variavel a qual nao possui definicao.
		printf("Linker error:SIMBOLO NAO DEFINIDO:");
		cout << symbol;
		printf("\n");
		this->linkerHaveProblem = true;
		return 0;
	}

	return map->second;
}

void LinkerEngine::ResolveCorrecaoEnderecos(){// Funcao em que corrige os enderecos relativos dos codigos objetos
	for (int i = 1; i < numberOfModules; i++) {
		auto objectCode = this->listOfModules[i].GetListaObjectCode();
		auto tableRealocation = this->listOfModules[i].GetTableRealocation();
		for (int z = 0; z < objectCode.size(); z++) {
			if(tableRealocation[z]=='1' && !objectCode[z].GetIsChanged()) {
				objectCode[z]=this->listaFatoresCorerrecao[i] + objectCode[z].GetCode();		
			}

		}
		this->listOfModules[i].SetListaObjectCode(objectCode);
	}

}

void LinkerEngine::Merge(string outputFile) {//funcao que conecta os.o e assim cria o executavel.
	fstream outputStream;
	stringstream outputContent;
	outputStream.open(outputFile, std::fstream::out);
	
	ObtainGlobalDefinition();
	ResolveReferencesCross();
	ResolveCorrecaoEnderecos();

	if (!this->linkerHaveProblem) {//cria o executavel apenas se nao houver problemas no processo de ligacao do codigo
		printf("MERGED CODE :");
		for (int i = 0; i < numberOfModules; i++) {
			auto objectCode = this->listOfModules[i].GetListaObjectCode();
			for (int z = 0; z < objectCode.size(); z++) {
					printf(" %d", objectCode[z].GetCode());
					outputContent << objectCode[z].GetCode();
						outputContent << " ";

			}
			
		}
		outputStream << outputContent.rdbuf();
		outputStream.close();
	} else {
		printf("\n Erros de ligamento encontrados. O arquivo .exe nao foi gerado\n");
	}
}

