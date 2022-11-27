#include"main.hpp"



int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdLine, int nCmdShow){
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	#endif
	MAINWINDOW mw(L"[015]Ball", 500, 500, 20);
	
	mw.SetExStyle(mw.GetExStyle() | WS_EX_COMPOSITED);
	mw.Register();
	mw.DBuff.Enable(true);
	mw.Create();
	
	mw.FPSLock(60);
	
	mw.GameLoop([](LPVOID args){
		MAINWINDOW *wnd;
		wnd = (MAINWINDOW*)args;
		
		wnd->MoveBall();
		
	}, (LPVOID)&mw);
	
	mw.Show(nCmdShow);
	//ShowWindow(mw.GetHandle(), SW_MAXIMIZE);
	return mw.Message();
}