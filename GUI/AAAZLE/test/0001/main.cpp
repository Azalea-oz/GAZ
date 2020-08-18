#define UNICODE
#define USE_DEBUG (1)
#include"../../AAAZLE.hpp"
#include"class.hpp"




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DEBUG::DebugConsole::Get_Instance().Init();
	MYWINDOW mw(500, 500, "• Œ¸‚Á‚½");
	
	mw.WClassName("TestWindow").Register();
	mw.Create();
	mw.Show(nCmdShow);
	mw.Print();
	return mw.Message();
}