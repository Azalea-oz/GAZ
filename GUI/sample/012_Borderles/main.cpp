#include"main.hpp"



int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdLine, int nCmdShow){
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	#endif
	//FPSC mw;
	MAINWINDOW mw(L"DEBUG MODE[TRUE]");
	Dcomment(L"Create MAINWINDOWS Instance");
	
	Dcomment(L"Add ExStyle[WS_EX_COMPOSITED]");
	mw.SetExStyle(mw.GetExStyle() | WS_EX_COMPOSITED);
	
	Dcomment(L"Register MAINWINDOW");
	mw.Register();
	
	Dcomment(L"Create window");
	mw.Create();
	
	Dcomment(L"Show Mode[default]");
	mw.Show(nCmdShow);
	return mw.Message();
}