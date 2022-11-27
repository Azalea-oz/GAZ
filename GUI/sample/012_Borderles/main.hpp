#include"../../src/AAAZLE.hpp"
#include"../../src/UTIL/utility.hpp"

//#include"../../src/COMPO/BUTTON/button.hpp"

#include <thread>
#include <chrono>
#include <string>
#include <queue>

#define DEBUG_LEVEL(x) (x)

#define DEBUG_BOX_REGION 1

void Dcomment(std::wstring str){
	#ifdef AZ_TEST_DEBUG
	std::wcout << str << std::endl;
	#endif
}

class AZBUTTON : public AZ::GUI::WINDOW{
	std::wstring Name;
	COLORREF FrameColor;
	COLORREF ScreenColor;
	COLORREF TextColor;
	COLORREF TextBackColor;
	
	bool fPic;
public:
	AZBUTTON(int x, int y, std::wstring str) : WINDOW(x, y, str), fPic(false){
		Name = str;
	}
	
	AZ::GUI::CODE EPAINT(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, HDC hdc){
		RECT rc;
		
		GetClientRect(hwnd, &rc);
		
		Rectangle(hdc, 0, 0, GetSize()[0], GetSize()[1]);
		
		DrawTextW(hdc, Name.c_str(), Name.length(), &rc, DT_CENTER);
		
		return STOPEVE;
	}
	
	void UsePicture(bool f){
		fPic = f;
	}
};

class MAINWINDOW : public AZ::GUI::WINDOW{
	AZBUTTON CloseBTN;
	AZBUTTON MaxBTN;
	AZBUTTON MinBTN;
	
public:
	MAINWINDOW(std::wstring str) : WINDOW(310, 310, str), CloseBTN(30, 30, L"×"), MaxBTN(30, 30, L"×"), MinBTN(30, 30, L"×"){
		WClassName(L"DEBUGTEST");
		
		//SetWindowStyle(WS_POPUP);
		Child(CloseBTN, 40010);
		Child(MaxBTN, 40011);
		Child(MinBTN, 40012);
	}
	~MAINWINDOW(){
		DeleteObject(hpen);
		DeleteObject(hbrush);
		//DeleteObject(hrgn);
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		
		#ifdef AZ_TEST_DEBUG
		#	if AZ_TEST_DEBUG >= DEBUG_LEVEL(DEBUG_BOX_REGION)
		RECT rc = {0, 0, GetSize()[0], GetSize()[1]};
		FillRect(hdc, &rc, hbrush);
		#	endif
		#endif
		
		TextOutW(hdc, 5, 10, std::wstring(L"Hello World").c_str(), std::wstring(L"Hello World").length());
		
		return 0;
	}
	AZ::GUI::CODE EKEY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(msg){
		case WM_KEYDOWN:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}
		
		return STOPEVE;
	}
	
};