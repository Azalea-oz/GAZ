#include <ole2.h>
#include <gdiplus.h>
#include"AAAZLE.hpp"
#include"testmain2.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DEBUG::DebugConsole::Get_Instance().Init();
	
	Gdiplus::GdiplusStartupInput gdiplusStartupInput; // MSDNにそのままのコードがある.
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	//AZ::GUI::WINDOW::UseUnicode(false);
	MYWINDOW mw(500, 500, L"ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ");
	
	
	MYWINDOW mw2(400, 400, L"my2");
	
	
	BTNWINDOW bw2(100, 50, L"貴族");
	BTNWINDOW bw3(100, 50, L"平民");
	
	mw.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MainWindow").Register();
	mw.WindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_VSCROLL).WindowPos(0, 0);
	//mw.Borderless();
	
	mw2.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"my2").Register();
	mw2.WindowStyle(WS_CHILD | WS_VISIBLE | WS_VISIBLE);
	mw.Child(mw2, (HMENU)ID_BUTTON);
	
	
	bw2.WClassName(L"BUTTON");
	bw2.WindowExStyle(0).WindowStyle(WS_CHILD | WS_VISIBLE | BS_OWNERDRAW).WindowPos(0, 0);
	bw2.Layout([](HDC hdc){
		DEBUG::DebugConsole::Get_Instance().Log("BTN layer was called");
		LineTo(hdc, 100, 50);
		MoveToEx(hdc, 100, 0, NULL);
		LineTo(hdc, 0, 50);
		
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Image image(L"IMG/test_red.bmp");
		graphics.DrawImage(&image, 0, 0, image.GetWidth() * 2, image.GetHeight());
		
		return 0;
	});
	
	mw2.Child(bw2, (HMENU)ID_BUTTON);
	
	bw3.WClassName(L"BUTTON");
	bw3.WindowExStyle(0).WindowStyle(WS_CHILD | WS_VISIBLE).WindowPos(100, 0);
	mw2.Child(bw3, (HMENU)ID_BUTTON2);
	
	
	mw.Layout([](HDC hdc){
		Rectangle(hdc , 0 , 0 , 500 , 500);
		LineTo(hdc, 500, 500);
		MoveToEx(hdc, 0, 500, NULL);
		LineTo(hdc, 500, 0);
		return 0;
	});
	
	mw2.Layout([](HDC hdc){
		Rectangle(hdc , 0 , 0 , 400 , 400);
		LineTo(hdc, 400, 400);
		MoveToEx(hdc, 0, 400, NULL);
		LineTo(hdc, 400, 0);
		return 0;
	});
	
	mw.Create();
	//mw.Print();
	mw.Show(nCmdShow);
	
	return mw.Message();
}