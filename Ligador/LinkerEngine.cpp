#include "LinkerEngine.h"

LinkerEngine::LinkerEngine(){
}

void LinkerEngine::AddModule(ModuleEngine  module){
	this->listOfModules.push_back(module);
	auto sizeCodigoObjeto=module.GetListaObjectCode().size();
	if (this->numberOfModules > 0) {
		this->correctionFactor.push_back(module.GetListaObjectCode()[sizeCodigoObjeto - 1].GetAddress() + 1 + correctionFactor[numberOfModules-1]);
		this->numberOfModules = this->numberOfModules + 1;
		return;
	}
	this->correctionFactor.push_back(module.GetListaObjectCode()[sizeCodigoObjeto - 1].GetAddress() + 1);
	this->numberOfModules = this->numberOfModules + 1;
	
}

void LinkerEngine::ObtainGlobalDefinition() {
	for (int i = 0; i < numberOfModules; i++) {
		auto listaDefinicao  = this->listOfModules[i].GetTableDefenition();
		//soma o fator de correcao
		for (int y = 0; y < listaDefinicao.size(); y++) {
			if (i > 0) {
				listaDefinicao[y].SetCorrecao(this->correctionFactor[i-1]);
				
			}
			auto aux = listaDefinicao[y];
			cout << aux.GetVariableName();
			printf("--%d \n",aux.GetVariableAdress());
			this->tableGlobalDefinition.push_back(aux);
		}
	}
}


