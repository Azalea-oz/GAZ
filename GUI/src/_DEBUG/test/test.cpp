#include"main.hpp"

class LDLL{
	HMODULE dll;
public:
	LDLL(std::string str){
		dll = LoadLibrary(str.c_str());
		if (dll == NULL){
			str += " : DLL�̓ǂݍ��݂Ɏ��s���܂����B";
			std::puts(str.c_str());
		}
	}
	~LDLL(){
		FreeLibrary(dll);
	}
	bool Load(std::string str){
		dll = LoadLibrary(str.c_str());
		if (dll == NULL){
			str += " : DLL�̓ǂݍ��݂Ɏ��s���܂����B";
			std::puts(str.c_str());
			return false;
		}
		
		return true;
	}
};

int main(){
	LDLL dll1("test.dll"), dll2("main.dll");
	
	
	
	
	return 0;
}