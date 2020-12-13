#include"test.hpp"

void test(){
	
	#ifndef TEST
	std::cout << "TEST was not defined" << std::endl;
	#else
	std::cout << "TEST was defined" << std::endl;
	#endif
	
}