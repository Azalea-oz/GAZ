#include"calc.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	CALC CalcWindow;
	
	CalcWindow.Create();
	CalcWindow.Show(nCmdShow);
	return CalcWindow.Message();
}