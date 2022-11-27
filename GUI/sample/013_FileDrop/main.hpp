#include"../../src/AAAZLE.hpp"







class MAINWINDOW : public AZ::GUI::WINDOW{
	
public:
	MAINWINDOW(std::wstring str) : WINDOW(300, 300, str){
		WClassName(str);
		//SetExStyle(GetExStyle() | WS_EX_ACCEPTFILES);
	}
	~MAINWINDOW(){}
	
	
	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		//DragAcceptFiles(hwnd, TRUE);
		return DEFAULTEVE;
	}
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		TextOutW(hdc, 0, 0, std::wstring(L"Hello World").c_str(), std::wstring(L"Hello World").length());
		TextOutW(hdc, 0, 20, std::wstring(L"こんにちは").c_str(), std::wstring(L"こんにちは").length());
		
		return 0;
	}
	
	AZ::GUI::CODE EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		
		MessageBoxW(NULL, L"FILE DROP", L"TEST", MB_OK);
		
		return DEFAULTEVE;
	}
	
	AZ::GUI::CODE EMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		
		switch(msg){
		case WM_LBUTTONUP:
			MessageBoxW(NULL, L"FILE DROP", L"TEST", MB_OK);
			break;
		}
		return DEFAULTEVE;
	}
};