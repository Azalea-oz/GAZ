#include"AAAZLE.hpp"

//#define ID_BUTTON 1200;
#define ID_BUTTON2 1201

#define USE_DEBUG (1)

class MYWINDOW : public AZ::GUI::WINDOW{
public:
	MYWINDOW(int w, int h) : WINDOW(w, h){}
	MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
	~MYWINDOW(){}
	CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		DEBUG::DebugConsole::Get_Instance().Log("Called Main Window EPAINT");
		
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc , 0 , 0 , 500 , 500);
		EndPaint(hwnd, &ps);
		return 1;
	}
	CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		if (IDYES == MessageBox(hwnd, "end", "Confirmation", MB_YESNO)) {
			DestroyWindow(hwnd);
		}
		return 0;
	}
	CODE ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
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
};
class BTNWINDOW : public AZ::GUI::WINDOW{
public:
	BTNWINDOW(int w, int h) : WINDOW(w, h){}
	BTNWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
	~BTNWINDOW(){}
	CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		DEBUG::DebugConsole::Get_Instance().Log("Called Button Window EPAINT");
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		Gdiplus::Graphics gra(hdc);
		
		Gdiplus::Pen MyPen(Gdiplus::Color(255, 0, 0, 255), 5);
		
		gra.DrawLine(&MyPen, 0, 0, 20, 20);
		
		EndPaint(hwnd, &ps);
		return 1;
	}
	CODE ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(msg){
		case WM_ERASEBKGND:
			return 1L;
		}
		return 1;
	}
	
	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DEBUG::DebugConsole::Get_Instance();
	MYWINDOW mw(500, 500, "noblesse oblige");
	BTNWINDOW mw2(100, 50, "‹M‘°");
	BTNWINDOW mw3(100, 50, "•½–¯");
	mw.WClassStyle(CS_HREDRAW | CS_VREDRAW).Register();
	
	mw2.WClassName("BUTTON");
	mw2.WindowExStyle(0).WindowStyle(WS_CHILD | WS_VISIBLE | BS_OWNERDRAW).WindowPos(0, 0);
	mw.Child(mw2, (HMENU)ID_BUTTON);
	
	mw3.WClassName("BUTTON");
	mw3.WindowExStyle(0).WindowStyle(WS_CHILD | WS_VISIBLE).WindowPos(100, 0);
	mw.Child(mw3, (HMENU)ID_BUTTON2);
	
	mw.Create();
	
	mw.Print();
	mw.Show(nCmdShow);
	return mw.Message();
}