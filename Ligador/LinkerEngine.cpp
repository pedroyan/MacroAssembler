#include "LinkerEngine.h"

LinkerEngine::LinkerEngine(){
}

void LinkerEngine::AddModule(ModuleEngine  module){
	this->listOfModules.push_back(module);
	auto sizeCodigoObjeto=module.GetListaObjectCode().size();
	if (this->numberOfModules > 0) {//calcula o fator de correcao para o proximo modulo
		this->listaFatoresCorerrecao.push_back(module.GetListaObjectCode()[sizeCodigoObjeto - 1].GetAddress() + 1 + listaFatoresCorerrecao[numberOfModules-1]);
		this->numberOfModules = this->numberOfModules + 1;
		return;
	}//calcula o fator de correcao para o proximo modulo caso nao tennha modulos anteriores
	this->listaFatoresCorerrecao.push_back(module.GetListaObjectCode()[sizeCodigoObjeto - 1].GetAddress() + 1);
	this->numberOfModules = this->numberOfModules + 1;
	
}

void LinkerEngine::ObtainGlobalDefinition() {
	for (int i = 0; i < numberOfModules; i++) {
		auto listaDefinicao  = this->listOfModules[i].GetTableDefenition();
		for (int y = 0; y < listaDefinicao.size(); y++) {
			if (i > 0) {
				listaDefinicao[y].AddFatorCorrecao(this->listaFatoresCorerrecao[i-1]);
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
		auto objectCode = this->listOfModules[i].GetListaObjectCode();
		auto tabelaUso = this->listOfModules[i].GetGetTableUse();
		for (int y = 0; y < tabelaUso.size(); y++) {
			auto enderecoParaAtulizar = tabelaUso[y].GetVariableAdress() - 1;
			auto newAdress = GetVarAdressGlobalTable(tabelaUso[y].GetVariableName());
			for (int z = 0; z < objectCode.size(); z++) {
				if (objectCode[z].GetAddress() == enderecoParaAtulizar) {
					objectCode[z].SetVarAdress(newAdress+objectCode[z].GetVarAdress());
					objectCode[z].SetIsChanged(true);
					break;
				}

			}
			
		}
		this->listOfModules[i].SetListaObjectCode(objectCode);
		this->listOfModules[i].SetGetTableUse(tabelaUso);
	}
}

int LinkerEngine::GetVarAdressGlobalTable(string symbol){
	auto map = this->tableGlobalDefinition.find(symbol);
	return map->second;
}


