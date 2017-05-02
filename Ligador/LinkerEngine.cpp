#include "LinkerEngine.h"

LinkerEngine::LinkerEngine(){
}

void LinkerEngine::AddModule(ModuleEngine  module){
	this->listOfModules.push_back(module);
	auto sizeCodigoObjeto=module.GetListaObjectCode().size();
	if (this->numberOfModules > 0) {
		this->listaFatoresCorerrecao.push_back(module.GetListaObjectCode()[sizeCodigoObjeto - 1].GetAddress() + 1 + listaFatoresCorerrecao[numberOfModules-1]);
		this->numberOfModules = this->numberOfModules + 1;
		return;
	}
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
			this->tableGlobalDefinition.push_back(enderecoRelativo);
		}
	}
}


