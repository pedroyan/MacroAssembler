#include "LinkerEngine.h"

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

void LinkerEngine::ObtainGlobalDefinition() {
	for (int i = 0; i < numberOfModules; i++) {
		auto listaDefinicao  = this->listOfModules[i].GetTableDefenition();
		for (int y = 0; y < listaDefinicao.size(); y++) {
			if (i > 0) {
				listaDefinicao[y].AddFatorCorrecao(this->listaFatoresCorerrecao[i]);
			}
			auto enderecoRelativo = listaDefinicao[y];
		//	cout << enderecoRelativo.GetVariableName();
		//	printf("--%d \n",enderecoRelativo.GetVariableAdress());
			this->tableGlobalDefinition.emplace(enderecoRelativo.GetVariableName(), enderecoRelativo.GetVariableAdress());
		//	this->tableGlobalDefinition.push_back(enderecoRelativo);
		}
	}
}

void LinkerEngine::ResolveReferencesCross(){
	for (int i = 0; i < numberOfModules; i++) {
		//guarda a tabela de uso e codigoObjeto de cada modulo
		auto objectCode = this->listOfModules[i].GetListaObjectCode();
		auto tabelaUso = this->listOfModules[i].GetGetTableUse();
		for (int y = 0; y < tabelaUso.size(); y++) {
			//para cada modulo,analisa a tabela de uso e muda o endereco de seus dados
			auto enderecoParaAtulizar = tabelaUso[y].GetVariableAdress();
			auto newAdress = GetVarAdressGlobalTable(tabelaUso[y].GetVariableName());
			objectCode[enderecoParaAtulizar] = newAdress+ objectCode[enderecoParaAtulizar]- listaFatoresCorerrecao[i];

			
			
		}
		this->listOfModules[i].SetListaObjectCode(objectCode);
	}
}

int LinkerEngine::GetVarAdressGlobalTable(string symbol){
	auto map = this->tableGlobalDefinition.find(symbol);
	if (map == this->tableGlobalDefinition.end()) {
		printf("Linker error:SIMBOLO NAO DEFINIDO:");
		cout << symbol;
		printf("\n");
		this->linkerHaveProblem = true;
		return 0;
	}

	return map->second;
}

void LinkerEngine::ResolveCorrecaoEnderecos(){
	for (int i = 1; i < numberOfModules; i++) {
		auto objectCode = this->listOfModules[i].GetListaObjectCode();
		auto tableRealocation = this->listOfModules[i].GetTableRealocation();
		for (int z = 0; z < objectCode.size(); z++) {
			if(tableRealocation[z]=='1') {
				objectCode[z]=this->listaFatoresCorerrecao[i] + objectCode[z];		
			}

		}
		this->listOfModules[i].SetListaObjectCode(objectCode);
	}

}

void LinkerEngine::Merge() {
	ObtainGlobalDefinition();
	ResolveReferencesCross();

	if (!this->linkerHaveProblem) {
		printf("MERGED CODE :");
		for (int i = 0; i < numberOfModules; i++) {
			auto objectCode = this->listOfModules[i].GetListaObjectCode();
			for (int z = 0; z < objectCode.size(); z++) {
					printf(" %d", objectCode[z]);
				
			}
		}
	} else {
		printf("\n Erros de ligamento encontrados. O arquivo .exe nao foi gerado\n");
	}
}


