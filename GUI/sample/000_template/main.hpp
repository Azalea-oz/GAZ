#include"../../src/AAAZLE.hpp"







class MAINWINDOW : public AZ::GUI::WINDOW{
	
public:
	MAINWINDOW(std::wstring str) : WINDOW(300, 300, str){
		WClassName(L"TemplateWindow").Register();
	}
	~MAINWINDOW(){}
	
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){
		TextOutW(hdc, 0, 0, std::wstring(L"Hello World").c_str(), std::wstring(L"Hello World").length());
		TextOutW(hdc, 0, 20, std::wstring(L"こんにちは").c_str(), std::wstring(L"こんにちは").length());
		
		return 0;
	}
	
	
};