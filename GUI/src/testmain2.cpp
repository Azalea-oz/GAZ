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


class BTNTEST : public AZ::GUI::WINDOW{
public:
	BTNTEST(int w, int h, std::wstring str) : WINDOW(w, h, str){
		WClassName(L"BUTTON");
		SetWindowStyle(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON);
		//SetWindowStyle(WS_CHILD | WS_VISIBLE);
		SetExStyle(0);
	}
	AZ::GUI::CODE ECREATE(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
		
		return DEFAULTEVE;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		#ifdef AZ_DEBUG
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "BTNTEST EPAINT was called");
		//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "BTNTEST EPAINT was called");
		#endif
		return STOPEVE;
	}
};
/*
std::function<long long(void)> CurrentTimeMicro = [](){
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
};
*/


AZMAIN(hInstance, hPrevInstance, lpCmdLine, nCmdShow){
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Init();
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- DEBUG START --------------");
	
	#ifdef AZ_STR_ENCODE
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Encode type --");
	switch(AZ_STR_ENCODE){
	case STR_ENCODE_SJIS:
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "SJIS");
		break;
	case STR_ENCODE_UNICODE:
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "UNICODE");
		break;
	}
	#endif
	#endif
	
	//AZ::GUI::WINDOW::UseUnicode(false);
	
	//MYWINDOW mw(500, 500, L"\u96F6零零零");
	MYWINDOW mw(500, 500, L"ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ");
	//MYWINDOW mw2(250, 250, L"my2");
	//MYWINDOW mw3(250, 250, L"my3");
	//MYWINDOW mw4(250, 250, L"my4");
	
	mw.WClassName(L"MainWindow").Register();
	
	/*
	BTNTEST bw2(100, 50, L"貴族");
	BTNTEST bw3(100, 50, L"平民");
	BTNTEST bw4(100, 50, L"貴族2");
	*/
	BTNWINDOW bw2(100, 50, L"貴族");
	BTNWINDOW bw3(100, 50, L"平民");
	BTNWINDOW bw4(100, 50, L"貴族2");
	
	//mw.Borderless();
	
	//mw2.WClassName(L"my2").Register();
	//mw4.WClassName(L"my4").Register();
	
	// WindowStyle を設定後Create時に反映させたい
	//mw2.SetChild(true);
	//mw2.WindowPos(250, 0).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	//mw.Child(mw2, (HMENU)0);
	
	//mw3.WClassName(L"my2");
	//mw3.WindowPos(0, 250).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	//mw.Child(mw3, (HMENU)0);
	
	//mw4.WindowPos(250, 250).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	//mw.Child(mw4, (HMENU)0);
	
	/*
	bw2.Layout([](HDC hdc){
		DEBUG::DebugConsole::Get_Instance().Log("BTN2 layer was called");
		LineTo(hdc, 100, 50);
		MoveToEx(hdc, 100, 0, NULL);
		LineTo(hdc, 0, 50);
		return 0;
	});
	*/
	/*
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
	
	mw4.Layout([](HDC hdc){
		
		auto tmp = SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0xff)));
		
		POINT p[3];
		p[0].x = 200; p[0].y = 0;
		p[1].x = 200; p[1].y = 200;
		p[2].x = 0; p[2].y = 200;
		Polygon(hdc, p, 3);
		
		DeleteObject(SelectObject(hdc, tmp));
		tmp = SelectObject(hdc, CreateSolidBrush(RGB(0xa0, 0xa0, 0xff)));
		
		
		p[0].x = 0; p[0].y = 0;
		p[1].x = 200; p[1].y = 0;
		p[2].x = 0; p[2].y = 200;
		Polygon(hdc, p, 3);
		
		DeleteObject(SelectObject(hdc, tmp));
		tmp = SelectObject(hdc, CreateSolidBrush(RGB(0xff, 0, 0)));
		
		int n = 3;
		PatBlt(hdc, 0, 0, 200 - n, 0, PATCOPY);
		PatBlt(hdc, 0, 0, 0, 200 - n, PATCOPY);
		PatBlt(hdc, n, n, 200 - n - n, 200 - n - n, PATCOPY);
		
		
		DeleteObject(SelectObject(hdc, tmp));
		return 0;
	});
	*/
	
	bw2.WindowPos(50, 50);
	bw3.WindowPos(50, 100);
	bw4.WindowPos(100, 150);
	
	
	//mw2.Child(bw2, NULL/*(HMENU)ID_BUTTON2*/);
	//mw2.Child(bw3, NULL/*(HMENU)ID_BUTTON3*/);
	//mw2.Child(bw4, NULL/*(HMENU)ID_BUTTON4*/);
	
	
	mw.Child(bw2, (HMENU)0);
	mw.Child(bw3, (HMENU)ID_BUTTON3);
	mw.Child(bw4, (HMENU)ID_BUTTON4);
	
	
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- CREATE ------------");
	
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "\tChange title");
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "( つ•̀ω•́)つ・・*:・:・゜:==≡≡Σ=͟͟͞͞(✡)`Д´）ｸﾞﾍｯ!");
	#endif
	
	mw.Create();
	
	mw.ChangeTitle(L"( つ•̀ω•́)つ・・*:・:・゜:==≡≡Σ=͟͟͞͞(✡)`Д´）ｸﾞﾍｯ!");
	
	/*
	mw.GameLoop([](LPVOID args){
		MYWINDOW *mw = (MYWINDOW*)args;
		DEBUG::DebugConsole::Get_Instance().Log((unsigned int)mw->GetWait());
	}, (LPVOID)&mw);
	*/
	
	HWND hButton = CreateWindowExW(
		0, L"BUTTON", L"Default", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 100, 50, mw.GetHandle(), NULL, hInstance, NULL);
	
	
	
	#ifdef AZ_DEBUG
	DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- SHOW -------------");
	#endif
	mw.Show(nCmdShow);
	
	return mw.Message();
}