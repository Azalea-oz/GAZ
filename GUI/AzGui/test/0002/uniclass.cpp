#include"uniclass.hpp"
#define ID_BUTTON2 1201

#define USE_DEBUG (1)


MYWINDOW::MYWINDOW(int w, int h) : WINDOW(w, h){}
MYWINDOW::MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
MYWINDOW::MYWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){}
MYWINDOW::~MYWINDOW(){}

AZ::GUI::CODE MYWINDOW::ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
	int result = MessageBox(hwnd, "end", "Confirmation", MB_YESNO);
	if (IDYES != result) return 0;
	return 1;
}


BTNWINDOW::BTNWINDOW(int w, int h) : WINDOW(w, h){}
BTNWINDOW::BTNWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
BTNWINDOW::BTNWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){}
BTNWINDOW::~BTNWINDOW(){}

AZ::GUI::CODE BTNWINDOW::ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
	switch(msg){
	case WM_ERASEBKGND:
		return 1L;
	}
	return 1;
}

AZ::GUI::CODE BTNWINDOW::EVENT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
	switch(LOWORD(wp)){
	case ID_BUTTON:
		DEBUG::DebugConsole::Get_Instance().Log("Button Clicked");
		break;
	case ID_BUTTON2:
		DEBUG::DebugConsole::Get_Instance().Log("Button Clicked 2");
		break;
	}
	return 1;
}
