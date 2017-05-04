#pragma once
class ObjectCode{
	public:
		ObjectCode(int code);
		int GetCode();
		void SetCode(int newCode);
		void SetIsChanged(bool isChanged);
		bool GetIsChanged();


	private:
		int code;
		bool isChanged=false;
	
};

