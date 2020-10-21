#include<ole2.h>
#include<gdiplus.h>
#include"AAAZLE.hpp"
#include"testmain2.hpp"

#define ID_MW2 40002
#define ID_MW3 40003
#define ID_NULL 100000

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	//FreeConsole();
	//DEBUG::DebugConsole::Get_Instance().Init();
	
	
	
	//AZ::GUI::WINDOW::UseUnicode(false);
	MYWINDOW mw(500, 500, L"\u96F6零零零");
	//MYWINDOW mw(500, 500, L"ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ");
	MYWINDOW mw2(250, 250, L"my2");
	MYWINDOW mw3(250, 250, L"my3");
	
	BTNWINDOW bw2(100, 50, L"貴族");
	BTNWINDOW bw3(100, 50, L"平民");
	BTNWINDOW bw4(100, 50, L"貴族2");
	
	IMG testImg(L"IMG/Editor_1.png");
	IMG testImg2(L"IMG/button_1.png");
	testImg.WClassName(L"IMG/Editor_1").Register();
	mw.Child(testImg, nullptr);
	testImg2.WClassName(L"IMG/button_1").Register();
	testImg2.WindowPos(300, 0).WindowStyle(WS_CHILD | WS_VISIBLE);
	mw.Child(testImg2, nullptr);
	
	mw.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MainWindow").Register();
	mw.WindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_VSCROLL).WindowPos(0, 0).WindowExStyle(0);
	//mw.Borderless();
	
	mw2.WClassName(L"my2").Register();
	mw2.WindowStyle(WS_CHILD);
	mw.Child(mw2, (HMENU)0);
	
	mw3.WClassName(L"my2");
	mw3.WindowStyle(WS_CHILD);
	mw.Child(mw3, (HMENU)0);
	
	
	//bw2.WClassName(L"BUTTON");
	//bw2.WindowExStyle(0).WindowStyle(WS_VISIBLE).WindowPos(0, 0);
	/*
	bw2.Layout([](HDC hdc){
		DEBUG::DebugConsole::Get_Instance().Log("BTN2 layer was called");
		LineTo(hdc, 100, 50);
		MoveToEx(hdc, 100, 0, NULL);
		LineTo(hdc, 0, 50);
		return 0;
	});
	*/
	//mw2.Child(bw2, (HMENU)ID_BUTTON2);
	
	
	//bw3.WClassName(L"BUTTON");
	//bw3.WindowExStyle(0).WindowStyle(WS_VISIBLE).WindowPos(100, 0);
	//mw2.Child(bw3, (HMENU)ID_BUTTON3);
	
	
	//bw4.WClassName(L"BUTTON");
	//bw4.WindowExStyle(0).WindowStyle(WS_VISIBLE ).WindowPos(50, 50);
	//mw2.Child(bw4, (HMENU)ID_BUTTON4);
	
	mw.Create();
	
	
	mw.Show(nCmdShow);
	
	return mw.Message();
}