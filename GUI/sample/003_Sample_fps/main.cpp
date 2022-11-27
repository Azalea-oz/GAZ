#include"main.hpp"



int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdLine, int nCmdShow){
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	#endif
	//FPSC mw;
	FPSC mw(60);
	
	mw.SetExStyle(mw.GetExStyle() | WS_EX_COMPOSITED);
	mw.Register();
	mw.Create();
	
	mw.GameLoop([](LPVOID args){
		FPSC *fps;
		fps = (FPSC*)args;
		fps->CountUp();
		fps->Calcfps();
		fps->Update();
	}, (LPVOID)&mw);
	
	mw.Wait([](LPVOID args){
		((FPSC*)args)->testWait();
	}, (LPVOID)&mw);
	
	mw.Show(nCmdShow);
	return mw.Message();
}