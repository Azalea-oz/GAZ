#include"AzDebug.hpp"
#include<iostream>
#include"util.hpp"

int main(){
	std::cout << DEBUG::UTIL::WStoS(L"logtest.log") << std::endl;
	
	DEBUG::DebugConsole::Get_Instance().Init(L"logtest.log");
	//DEBUG::error_dialog(NULL, L"test error_dialog()");
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Start");
	
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"ID_NONE");
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_WARNING, L"ID_WARNING");
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_ERROR, L"ID_ERROR");
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_SAFE, L"ID_SAFE");
	
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Finish");
	
	char tmp;
	std::cin >> tmp;
	return 0;
}