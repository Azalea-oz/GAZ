#include"singleton.hpp"
#include<iostream>

class child : public SINGLETON::Singleton<child>{
	int value;
	
public:
	child() : value(10){}
	~child(){}
	
	void set(int v){Get_Instance().value = v;}
	void print(){
		std::cout << this << std::endl;
		std::cout << Get_Instance().value << std::endl;
	}
};

int main(){
	
	child ch;
	ch.print();
	ch.set(100);
	
	child ch2;
	ch2.print();
	
	return 0;
}