#include<ole2.h>
#include<gdiplus.h>
#include <thread>
#include <chrono>
#include <string>
#include"AAAZLE.hpp"
#include"testmain2.hpp"

#define ID_MW2 40002
#define ID_MW3 40003
#define ID_NULL 100000



/*
std::function<long long(void)> CurrentTimeMicro = [](){
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
};
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	DEBUG::DebugConsole::Get_Instance().Log("-- DEBUG START --------------");
	#endif
	
	
	//AZ::GUI::WINDOW::UseUnicode(false);
	
	MYWINDOW mw(500, 500, L"\u96F6零零零");
	//MYWINDOW mw(500, 500, L"ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ");
	MYWINDOW mw2(250, 250, L"my2");
	MYWINDOW mw3(250, 250, L"my3");
	
	mw.WClassName(L"MainWindow").Register();
	
	BTNWINDOW bw2(100, 50, L"貴族");
	BTNWINDOW bw3(100, 50, L"平民");
	BTNWINDOW bw4(100, 50, L"貴族2");
	
	//IMG testImg(L"IMG/Editor_1.png");
	//IMG testImg2(L"IMG/button_1.png");
	//testImg.WClassName(L"IMG/Editor_1").Register();
	//mw.Child(testImg, nullptr);
	//testImg2.WClassName(L"IMG/button_1").Register();
	//testImg2.WindowPos(300, 0).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	//mw.Child(testImg2, nullptr);
	
	//mw.Borderless();
	
	mw2.WClassName(L"my2").Register();
	
	// WindowStyle を設定後Create時に反映させたい
	//mw2.SetChild(true);
	mw2.WindowPos(250, 0).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	mw.Child(mw2, (HMENU)0);
	
	mw3.WClassName(L"my2");
	mw3.WindowPos(0, 250).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	mw.Child(mw3, (HMENU)0);
	
	/*
	bw2.Layout([](HDC hdc){
		DEBUG::DebugConsole::Get_Instance().Log("BTN2 layer was called");
		LineTo(hdc, 100, 50);
		MoveToEx(hdc, 100, 0, NULL);
		LineTo(hdc, 0, 50);
		return 0;
	});
	*/
	
	mw.Layout([](HDC hdc){
		
		auto tmp = SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0xff)));
		PatBlt(hdc, 100, 100, 100, 100, PATCOPY);
		DeleteObject(SelectObject(hdc, tmp));
		
		return 0;
	});
	
	mw2.Layout([](HDC hdc){
		
		auto tmp = SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0xff)));
		PatBlt(hdc, 0, 0, 100, 100, PATCOPY);
		DeleteObject(SelectObject(hdc, tmp));
		
		return 0;
	});
	
	
	
	bw2.WindowPos(50, 50);
	bw3.WindowPos(50, 100);
	bw4.WindowPos(100, 150);
	
	
	mw2.Child(bw2, (HMENU)ID_BUTTON2);
	mw2.Child(bw3, (HMENU)ID_BUTTON3);
	mw2.Child(bw4, (HMENU)ID_BUTTON4);
	
	/*
	mw.Child(bw2, (HMENU)ID_BUTTON2);
	mw.Child(bw3, (HMENU)ID_BUTTON3);
	mw.Child(bw4, (HMENU)ID_BUTTON4);
	*/
	
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Log("-- CREATE ------------");
	#endif
	mw.Create();
	/*
	mw.GameLoop([](LPVOID args){
		MYWINDOW *mw = (MYWINDOW*)args;
		DEBUG::DebugConsole::Get_Instance().Log((unsigned int)mw->GetWait());
	}, (LPVOID)&mw);
	*/
	
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Log("-- SHOW -------------");
	#endif
	mw.Show(nCmdShow);
	
	return mw.Message();
}