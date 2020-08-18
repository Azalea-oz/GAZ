#include"AzDebug.hpp"
#include<iostream>

int main(){
	DEBUG::DebugConsole dbc;
	dbc.Init();
	
	dbc.Log("Start");
	dbc.Log("Finish");

	char tmp;
	std::cin >> tmp;
	return 0;
}