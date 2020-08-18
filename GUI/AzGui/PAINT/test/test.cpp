#include<iostream>
#include"../paint.hpp"


int main(){
	AZ::GUI::PAINT::RGB32 rgb;
	
	
	std::cout << (int)rgb.R << std::endl;
	std::cout << (int)rgb.G << std::endl;
	std::cout << (int)rgb.B << std::endl;
	std::cout << (int)rgb.A << std::endl;
	
	//rgb.R = 0xff;
	//rgb.G = 0xff;
	//rgb.B = 0xff;
	//rgb.A = 0xff;
	
	std::cout << "----" << std::endl;
	std::cout << rgb.isBlack() << std::endl;
	std::cout << rgb.isWhite() << std::endl;
	std::cout << rgb.isRed() << std::endl;
	std::cout << rgb.isGreen() << std::endl;
	std::cout << rgb.isBlue() << std::endl;
	std::cout << rgb.isInvisible() << std::endl;
	
	
	return 0;
}