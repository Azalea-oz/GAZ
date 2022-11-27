#define AZ_STR_ENCODE STR_ENCODE_UNICODE

#include"AAAZLE.hpp"
#include<dwmapi.h>
#include"SINGLETON/singleton.hpp"

#define ID_BUTTON2 1201
#define ID_BUTTON3 1202
#define ID_BUTTON4 1203
#define SCL1 1301



#define USE_DEBUG (1)

class BTNWINDOW : public AZ::GUI::WINDOW{
	bool Reg;
	
public:
	BTNWINDOW(int w, int h) : WINDOW(w, h){
		
		WClassName(L"BUTTON");
		SetExStyle(0).SetWindowStyle(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON);
	}
	/*
	BTNWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){
		WClassName("BUTTON");
		SetExStyle(0).SetWindowStyle(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON);
	}
	*/
	BTNWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){
		
		WClassName(L"BUTTON");
		SetExStyle(0).SetWindowStyle(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW);
	}
	~BTNWINDOW(){}
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		
		return DEFAULTEVE;
	}
	
	/*
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		//Rectangle(hdc, 0, 0, 100, 50);
		return DEFAULTEVE;
	}*/
	
	
	AZ::GUI::CODE CHILDMSG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		wchar_t tmp[256];
		switch(LOWORD(wp)){
		case ID_BUTTON:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Button Clicked -------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetClassName());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			#endif
			
			//Enable(false);
			break;
		case ID_BUTTON2:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Button2 Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetClassName());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			#endif
			
			//Enable(false);
			break;
		case ID_BUTTON3:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Button3 Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetClassName());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			#endif
			
			MessageBoxW(nullptr, L"Click", L"Button3", MB_OK);
			
			#ifdef AZ_DEBUG
			GetWindowTextW(GetParentHandle(), tmp, 256);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Change Title ------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)GetParentHandle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetParent().GetClassName());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetParent().GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, tmp);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			#endif
			
			//Enable(false);
			break;
		case ID_BUTTON4:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Button4 Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetClassName());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, msg);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			#endif
			
			MessageBoxW(nullptr, L"Click", L"Button4", MB_OK);
			
			break;
		}
		return 1;
	}
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		#ifdef AZ_DEBUG
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"epaint");
		#endif
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

class MYWINDOW : public AZ::GUI::WINDOW{
	bool title;
public:
	MYWINDOW(int w, int h) : WINDOW(w, h){
		WClassStyle(CS_HREDRAW | CS_VREDRAW);
		setTITLEDWINDOW(true).setVISIBLE(true);
		setSCROLL(false, true).setCAPTIONBOX(false, false, true);
		setCLIPCHILDREN(true);
		WindowPos(0, 0).SetExStyle(WS_EX_OVERLAPPEDWINDOW);
		title = false;
	}
	/*
	MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){
		WClassStyle(CS_HREDRAW | CS_VREDRAW);
		setTITLEDWINDOW(true).setVISIBLE(true);
		setSCROLL(false, true).setCAPTIONBOX(false, false, true);
		setCLIPCHILDREN(true);
		WindowPos(0, 0).SetExStyle(WS_EX_OVERLAPPEDWINDOW);
	}
	*/
	
	MYWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){
		WClassStyle(CS_HREDRAW | CS_VREDRAW);
		setTITLEDWINDOW(true).setVISIBLE(true);
		setSCROLL(false, true).setCAPTIONBOX(false, true, true);
		setCLIPCHILDREN(false);
		WindowPos(0, 0).SetExStyle(WS_EX_OVERLAPPEDWINDOW);
		title = false;
	}
	~MYWINDOW(){}
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		
		//it changes window title
		//ChangeTitle(L"( つ•̀ω•́)つ・・*:・:・゜:==≡≡Σ=͟͟͞͞(✡)`Д´）ｸﾞﾍｯ!");
		return 0;
	}
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBoxW(hwnd, L"end", L"Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
	AZ::GUI::CODE EDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		PostQuitMessage(0);
		return 0;
	}
	AZ::GUI::CODE EMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		ChangeTitle(L"( つ•̀ω•́)つ・・*:・:・゜:==≡≡Σ=͟͟͞͞(✡)`Д´）ｸﾞﾍｯ!");
		switch(msg){
		case WM_LBUTTONDOWN:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Clicked ------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "");
			#endif
			
			if(title){
				title = false;
				SendMessageW(GetHandle(), WM_SETTEXT, 0, (LPARAM)L"あいうえお");
			} else{
				title = true;
				SendMessageW(GetHandle(), WM_SETTEXT, 0, (LPARAM)L"( つ•̀ω•́)つ・・*:・:・゜:==≡≡Σ=͟͟͞͞(✡)`Д´）ｸﾞﾍｯ!");
			}
			
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
			break;
		}
		
		return 1;
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
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, str);
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
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Image is nullptr");
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


