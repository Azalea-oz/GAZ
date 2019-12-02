/*GUI.cpp*/

#include"Azgui.h"
#include"MainWindow.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShowCmd){
	MainWindow Main("Main");
	//OtherWindow Other("Other");

	//---Windowの作成---
	Main.InitWC();
	//Other.InitWC();

	//Other.NoMenu();
	
	

	if(Main.Create("タイトル") == false){
		return -1;
	}

	/*
	if (Other.Create("タイトル", pos) == false) {
		return -1;
	}
	*/

	return Main.LoopMsg();
	
	//-----------------
	
}

