#include"AzDebug.hpp"
#include<iostream>

int main(){
	DEBUG::DebugConsole::Get_Instance().Init();
	DEBUG::error_dialog(NULL);
	DEBUG::DebugConsole::Get_Instance().Log("Start");
	DEBUG::error_dialog(NULL);
	DEBUG::DebugConsole::Get_Instance().Log("Finish");
	DEBUG::error_dialog(NULL);
	
	char tmp;
	std::cin >> tmp;
	return 0;
}