#pragma once
class ObjectCode{//classe do codigo objeto
	public:
		ObjectCode(int code);
		int GetCode();
		void SetCode(int newCode);
		void SetIsChanged(bool isChanged);
		bool GetIsChanged();


	private:
		int code;
		bool isChanged=false;//bool para saber se a variavel relativa ja foi modificada durante o programa,asism ela nao sera alterada nas correcoes dos enderecos.
	
};

