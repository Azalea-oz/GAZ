#include"main.hpp"

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdLine, int nCmdShow){
	MAINWINDOW mw(40);
	
	mw.Register();
	mw.DBuff.Enable(true);
	mw.Create();
	
	mw.FPSLock(60);
	
	mw.GameLoop([](LPVOID args){
		MAINWINDOW *wnd;
		wnd = (MAINWINDOW*)args;
		
		wnd->countup();
		
	}, (LPVOID)&mw);
	
	mw.Show(nCmdShow);
	return mw.Message();
}