#include"main.hpp"



int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdLine, int nCmdShow){
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	#endif
	MAINWINDOW mw(L"Template Window");
	
	mw.Create();
	
	mw.Show(nCmdShow);
	return mw.Message();
}