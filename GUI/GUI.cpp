/*GUI.cpp*/

#include"Azgui.h"
#include"MainWindow.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShowCmd){
	MainWindow Main("Main");
	//OtherWindow Other("Other");

	//---Window�̍쐬---
	Main.InitWC();
	//Other.InitWC();

	//Other.NoMenu();
	
	

	if(Main.Create("�^�C�g��") == false){
		return -1;
	}

	/*
	if (Other.Create("�^�C�g��", pos) == false) {
		return -1;
	}
	*/

	return Main.LoopMsg();
	
	//-----------------
	
}

