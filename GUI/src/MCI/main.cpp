#include"../AAAZLE.hpp"
#include<vfw.h>

#define IDM_OPEN 10020

class Test : public AZ::GUI::WINDOW{
public:
	Test(int w, int h) : WINDOW(w, h){}
	Test(int w, int h, std::string str) : WINDOW(w, h, str){}
	Test(int w, int h, std::wstring str) : WINDOW(w, h, str){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		return 0;
	}
	
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBox(hwnd, "end", "Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
};


class MCITest : public AZ::GUI::WINDOW{
	HWND hmci;
	
public:
	MCITest(int w, int h) : WINDOW(w, h){}
	MCITest(int w, int h, std::string str) : WINDOW(w, h, str){}
	MCITest(int w, int h, std::wstring str) : WINDOW(w, h, str){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		hmci = MCIWndCreateW(hwnd , ((LPCREATESTRUCT)lp)->hInstance ,
			0 , L"song_kei_harujion.mp3");
		
		MoveWindow(hmci, 0, 200, 700, 100, true);
		
		return 0;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		Rectangle(hdc , 0 , 0 , GetSize()[0], GetSize()[1]);
		LineTo(hdc, GetSize()[0], GetSize()[1]);
		MoveToEx(hdc, 0, GetSize()[1], NULL);
		LineTo(hdc, GetSize()[0], 0);
		
		EndPaint(hwnd, &ps);
		return 1;
	}
	
	AZ::GUI::CODE EDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		MCIWndDestroy(hmci);
		PostQuitMessage(0);
		return 0;
	}
	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	Test test(700, 500, L"MCIテスト");
	MCITest Mt(700, 300, L"Mt");
	
	test.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"TestWindow").Register();
	test.WindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE).WindowPos(0, 0);
	
	Mt.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MCITestWindow").Register();
	Mt.WindowStyle(WS_CHILD | WS_VISIBLE).WindowPos(0, 0);
	
	test.Child(Mt, (HMENU)IDM_OPEN);
	
	test.Create();
	test.Show(nCmdShow);
	return test.Message();
}