#include"AAAZLE.hpp"
#define ID_BUTTON2 1201
#define ID_BUTTON3 1202
#define ID_BUTTON4 1203
#define SCL1 1301


#define USE_DEBUG (1)

class SCROLLONLY : public AZ::GUI::WINDOW{
	SCROLLINFO scr;
public:
	SCROLLONLY(int w, int h) : WINDOW(w, h){
		scr.cbSize = sizeof(SCROLLINFO);
		scr.fMask = SIF_ALL;
		scr.nMin = 0;	scr.nMax = 500;
		scr.nPage = 100;
		scr.nPos = 0;

		SetScrollInfo(GetHandle() , SB_CTL , &scr , TRUE);
		scr.fMask = SIF_POS;
	}
	SCROLLONLY(int w, int h, std::string str) : WINDOW(w, h, str){
		scr.cbSize = sizeof(SCROLLINFO);
		scr.fMask = SIF_ALL;
		scr.nMin = 0;	scr.nMax = 500;
		scr.nPage = 100;
		scr.nPos = 0;

		SetScrollInfo(GetHandle() , SB_CTL , &scr , TRUE);
		scr.fMask = SIF_POS;
	}
	SCROLLONLY(int w, int h, std::wstring str) : WINDOW(w, h, str){
		scr.cbSize = sizeof(SCROLLINFO);
		scr.fMask = SIF_ALL;
		scr.nMin = 0;	scr.nMax = 500;
		scr.nPage = 100;
		scr.nPos = 0;

		SetScrollInfo(GetHandle() , SB_CTL , &scr , TRUE);
		scr.fMask = SIF_POS;
	}
	~SCROLLONLY(){}
	
	AZ::GUI::CODE ESCROLL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(LOWORD(wp)) {
		case SB_TOP:
			scr.nPos = scr.nMin;
			break;
		case SB_BOTTOM:
			scr.nPos = scr.nMax;
			break;
		case SB_LINEUP:
			if (scr.nPos) scr.nPos--;
			break;
		case SB_LINEDOWN:
			if (scr.nPos < scr.nMax - 1) scr.nPos++;
			break;
		case SB_PAGEUP:
			scr.nPos -= scr.nPage;
			break;
		case SB_PAGEDOWN:
			scr.nPos += scr.nPage;
			break;
		case SB_THUMBPOSITION:
			scr.nPos = HIWORD(wp);
			break;
		}
		DEBUG::DebugConsole::Get_Instance().Log(scr.nPos);
		SetScrollInfo(GetHandle() , SB_CTL , &scr , TRUE);
		return 0;
	}
};

class MYWINDOW : public AZ::GUI::WINDOW{
	SCROLLINFO scr;
public:
	MYWINDOW(int w, int h) : WINDOW(w, h){}
	MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
	MYWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){}
	~MYWINDOW(){}
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		scr.cbSize = sizeof(SCROLLINFO);
		scr.fMask = SIF_PAGE | SIF_RANGE;
		scr.nMin = 0;	scr.nMax = 200;
		scr.nPage = 100;
		scr.nPos = 0;
		
		SetScrollInfo(hwnd , SB_VERT , &scr , TRUE);
		scr.fMask = SIF_POS;
		return 1;
	}
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBox(hwnd, "end", "Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
	
	AZ::GUI::CODE ESCROLL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(LOWORD(wp)) {
		case SB_TOP:
			scr.nPos = scr.nMin;
			break;
		case SB_BOTTOM:
			scr.nPos = scr.nMax;
			break;
		case SB_LINEUP:
			if (scr.nPos) scr.nPos--;
			break;
		case SB_LINEDOWN:
			if (scr.nPos < scr.nMax - 1) scr.nPos++;
			break;
		case SB_PAGEUP:
			scr.nPos -= scr.nPage;
			break;
		case SB_PAGEDOWN:
			scr.nPos += scr.nPage;
			break;
		case SB_THUMBPOSITION:
			scr.nPos = HIWORD(wp);
			break;
		}
		DEBUG::DebugConsole::Get_Instance().Log(scr.nPos);
		SetScrollInfo(hwnd , SB_VERT , &scr , TRUE);

		
		return 0;
	}
};
class BTNWINDOW : public AZ::GUI::WINDOW{
	SCROLLINFO scr;
public:
	BTNWINDOW(int w, int h) : WINDOW(w, h){}
	BTNWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
	BTNWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){}
	~BTNWINDOW(){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		scr.cbSize = sizeof(SCROLLINFO);
		scr.fMask = SIF_PAGE | SIF_RANGE;
		scr.nMin = 0;	scr.nMax = 9;
		scr.nPage = 2;

		SetScrollInfo(hwnd , SB_VERT , &scr , TRUE);
		scr.fMask = SIF_POS;
		
		DEBUG::DebugConsole::Get_Instance().Log("Scroll bar created");
		return 0;
	}
	
	AZ::GUI::CODE ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(msg){
		case WM_ERASEBKGND:
			return 1L;
		}
		return 1;
	}
	
	AZ::GUI::CODE ESCROLL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(LOWORD(wp)) {
		case SB_TOP:
			scr.nPos = scr.nMin;
			break;
		case SB_BOTTOM:
			scr.nPos = scr.nMax;
			break;
		case SB_LINEUP:
			if (scr.nPos) scr.nPos--;
			break;
		case SB_LINEDOWN:
			if (scr.nPos < scr.nMax - 1) scr.nPos++;
			break;
		case SB_PAGEUP:
			scr.nPos -= scr.nPage;
			break;
		case SB_PAGEDOWN:
			scr.nPos += scr.nPage;
			break;
		case SB_THUMBPOSITION:
			scr.nPos = HIWORD(wp);
			break;
		}
		DEBUG::DebugConsole::Get_Instance().Log(scr.nPos);
		SetScrollInfo(hwnd , SB_VERT , &scr , TRUE);

		
		return 0;
	}
	
	AZ::GUI::CODE EVENT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(LOWORD(wp)){
		case ID_BUTTON:
			DEBUG::DebugConsole::Get_Instance().Log("Button Clicked");
			break;
		case ID_BUTTON2:
			DEBUG::DebugConsole::Get_Instance().Log("Button Clicked 2");
			break;
		case ID_BUTTON3:
			DEBUG::DebugConsole::Get_Instance().Log("Button Clicked 3");
			break;
		case ID_BUTTON4:
			DEBUG::DebugConsole::Get_Instance().Log("Button Clicked 4");
			break;
		}
		return 1;
	}
};