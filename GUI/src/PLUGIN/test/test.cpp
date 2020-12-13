#include"test.hpp"
#include<iostream>

#define TEST_VERSION "0.00.01"


class Sample : public Test{
private:
	
public:
	Sample(){
		std::cout << "Sample's constructor was called" << std::endl;
	}
	
	~Sample(){
		std::cout << "Sample's destructor was called" << std::endl;
	}
	
	const char* version(void){
		return TEST_VERSION;
	}
};

extern "C"{
	Test* Create(void){
		return new Sample();
	}
}
