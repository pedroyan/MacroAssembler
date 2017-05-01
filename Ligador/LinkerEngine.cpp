#include "LinkerEngine.h"

LinkerEngine::LinkerEngine(){
}

void LinkerEngine::AddModule(ModuleEngine  module){
	this->listOfModules.push_back(module);
}
