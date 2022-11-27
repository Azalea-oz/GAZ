#include"main.hpp"
#include<locale>

#ifdef AZ_DEBUG
#include"../../DEBUG/debug.hpp"
#endif

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR lpCmdLine, int nCmdShow){
	
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	#endif
	
	//AZEDITOR mw(L"HTML Editor []");
	AZTEST mw(L"HTML Editor []");
	
	
	mw.Register();
	mw.Create();
	
	mw.Show(nCmdShow);
	return mw.Message();
}