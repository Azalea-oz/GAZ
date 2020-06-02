#include<iostream>
#include"AAAZLE.hpp"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	std::cout << "start" << std::endl;
	AZ::GUI::WINDOW mw(500, 100, "noblesse oblige");
	std::cout << "end" << std::endl;
	return 0;
}