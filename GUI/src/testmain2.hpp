#include"AAAZLE.hpp"
#include<dwmapi.h>
#include"SINGLETON/singleton.hpp"

#define ID_BUTTON2 1201
#define ID_BUTTON3 1202
#define ID_BUTTON4 1203
#define SCL1 1301



#define USE_DEBUG (1)

/*
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
		SetScrollInfo(GetHandle() , SB_CTL , &scr , TRUE);
		return 0;
	}
};
*/

class BTNWINDOW : public AZ::GUI::WINDOW{
	bool Reg;
	
public:
	BTNWINDOW(int w, int h) : WINDOW(w, h){
		WClassName(L"BUTTON");
		SetExStyle(0).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	}
	BTNWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){
		WClassName(L"BUTTON");
		SetExStyle(0).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	}
	BTNWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){
		WClassName(L"BUTTON");
		SetExStyle(0).SetWindowStyle(WS_CHILD | WS_VISIBLE);
	}
	~BTNWINDOW(){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		return 0;
	}
	
	
	AZ::GUI::CODE EVENT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(LOWORD(wp)){
		case ID_BUTTON:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- Button Clicked -------");
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(GetClassNameW());
			DEBUG::DebugConsole::Get_Instance().Log(GetTitleW());
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log("");
			#endif
			
			//Enable(false);
			break;
		case ID_BUTTON2:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- Button2 Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(GetClassNameW());
			DEBUG::DebugConsole::Get_Instance().Log(GetTitleW());
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log("");
			#endif
			
			//Enable(false);
			break;
		case ID_BUTTON3:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- Button3 Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(GetClassNameW());
			DEBUG::DebugConsole::Get_Instance().Log(GetTitleW());
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log("");
			#endif
			
			//Enable(false);
			break;
		case ID_BUTTON4:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- Button4 Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(GetClassNameW());
			DEBUG::DebugConsole::Get_Instance().Log(GetTitleW());
			DEBUG::DebugConsole::Get_Instance().Log(msg);
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log("");
			#endif
			
			break;
		}
		return 1;
	}
	
	/*
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		
		Rectangle(hdc , 0 , 0 , GetSize()[0], GetSize()[1]);
		LineTo(hdc, GetSize()[0], GetSize()[1]);
		MoveToEx(hdc, 0, GetSize()[1], NULL);
		LineTo(hdc, GetSize()[0], 0);
		
		return 1;
	}
	*/
};

class MYWINDOW : public AZ::GUI::WINDOW{
	
public:
	MYWINDOW(int w, int h) : WINDOW(w, h){
		WClassStyle(CS_HREDRAW | CS_VREDRAW);
		setTITLEDWINDOW(true).setVISIBLE(true);
		setSCROLL(false, true).setCAPTIONBOX(false, false, true);
		WindowPos(0, 0).SetExStyle(0);
	}
	MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){
		WClassStyle(CS_HREDRAW | CS_VREDRAW);
		setTITLEDWINDOW(true).setVISIBLE(true);
		setSCROLL(false, true).setCAPTIONBOX(false, false, true);
		WindowPos(0, 0).SetExStyle(0);
	}
	MYWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){
		WClassStyle(CS_HREDRAW | CS_VREDRAW);
		setTITLEDWINDOW(true).setVISIBLE(true);
		setSCROLL(false, true).setCAPTIONBOX(false, false, true);
		WindowPos(0, 0).SetExStyle(0);
	}
	~MYWINDOW(){}
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		
		//it changes window title
		ChangeTitle(L"( つ•̀ω•́)つ・・*:・:・゜:==≡≡Σ=͟͟͞͞(✡)`Д´）ｸﾞﾍｯ!");
		return 0;
	}
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBox(hwnd, "end", "Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
	AZ::GUI::CODE EDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		PostQuitMessage(0);
		return 0;
	}
	
	
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		
		auto tmp = SelectObject(hdc, CreateSolidBrush(RGB(0xff, 0, 0)));
		PatBlt(hdc, 0, 0, 200, 200, PATCOPY);
		DeleteObject(SelectObject(hdc, tmp));
		
		//Rectangle(hdc , 0 , 0 , GetSize()[0], GetSize()[1]);
		LineTo(hdc, GetSize()[0], GetSize()[1]);
		MoveToEx(hdc, 0, GetSize()[1], NULL);
		LineTo(hdc, GetSize()[0], 0);
		
		return DEFAULTEVE;
	}
	
};


/*gdiplus initializer*/
/*singleton*/
class InitGdiplus : protected SINGLETON::Singleton<InitGdiplus>{
	ULONG_PTR gdiplusToken;
public:
	InitGdiplus(){
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	 virtual ~InitGdiplus(){
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
	
};

class IMG : public AZ::GUI::WINDOW{
	InitGdiplus _GdiplusInit;
	Gdiplus::Bitmap *Image;
	HDC hDC;
public:
	IMG() : WINDOW(1, 1, L"AZIMG"), _GdiplusInit(){
		WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"IMGWindow");
		SetWindowStyle(WS_CHILD | WS_VISIBLE);
		Image = nullptr;
	}
	IMG(std::wstring _str) : WINDOW(1, 1, _str), _GdiplusInit(){
		WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"IMGWindow");
		//Mode.RelativeSize(true);
		SetWindowStyle(WS_CHILD | WS_VISIBLE);
		Image = new Gdiplus::Bitmap(_str.c_str());
	}
	~IMG(){
		if(Image != nullptr){
			delete Image;
			Image = nullptr;
		}
	}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		ReSizeWindow(GetParent().GetSize()[0], GetParent().GetSize()[1]);
		
		
		return 0;
	}
	AZ::GUI::CODE ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		ReSizeWindow(GetParent().GetSize()[0], GetParent().GetSize()[1]);
		
		
		return 0;
	}
	
	AZ::GUI::CODE ERELATIVESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		#ifdef AZ_DEBUG
		std::string str = std::to_string(GetSize()[0]) + std::string(" : ") + std::to_string(GetSize()[1]);
		DEBUG::DebugConsole::Get_Instance().Log(str);
		#endif
		ReSizeWindow(GetParent().GetSize()[0], GetParent().GetSize()[1]);
		//InvalidateRect(hwnd ,NULL ,true);
		
		return 0;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		Gdiplus::Graphics *g;
		g = new Gdiplus::Graphics(hdc);
		
		if(Image != nullptr) g->DrawImage(Image, 0, 0);
		else {
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("Image is nullptr");
			#endif
		}
		delete g;
		
		return 1;
	}
	
	void LoadImage(std::wstring _str){
		if(Image != nullptr){
			delete Image;
			Image = nullptr;
		}
		Image = new Gdiplus::Bitmap(_str.c_str());
	}
};
