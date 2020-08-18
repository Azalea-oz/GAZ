#include<string>
#include"../../AAAZLE.hpp"
#include"timer.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DEBUG::DebugConsole::Get_Instance().Init();
	//AZ::GUI::WINDOW::UseUnicode(true);
	
	TIMERMYWINDOW MainWindow(500, 500, L"Timer");
	MainWindow.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MainWindow").Register();
	
	mw2.WClassName(L"BUTTON");
	mw2.WindowExStyle(0).WindowStyle(WS_CHILD | WS_VISIBLE | BS_OWNERDRAW).WindowPos(0, 0);
	mw2.Layout([](HDC hdc){
		LineTo(hdc, 100, 50);
		MoveToEx(hdc, 100, 0, NULL);
		LineTo(hdc, 0, 50);
	});
	MainWindow.Child(mw2, (HMENU)ID_BUTTON);
	
	mw3.WClassName(L"BUTTON");
	mw3.WindowExStyle(0).WindowStyle(WS_CHILD | WS_VISIBLE).WindowPos(100, 0);
	MainWindow.Child(mw3, (HMENU)ID_BUTTON2);
	
	MainWindow.Layout([](HDC hdc){
		Rectangle(hdc , 0 , 0 , 500 , 500);
		LineTo(hdc, 500, 500);
		MoveToEx(hdc, 0, 500, NULL);
		LineTo(hdc, 500, 0);
		
	});
	
	MainWindow.Create();
	//MainWindow.Print();
	MainWindow.Show(nCmdShow);
	return MainWindow.Message();
}