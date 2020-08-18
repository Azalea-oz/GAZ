#include"AAAZLE.hpp"


class MYWINDOW : public AZ::GUI::WINDOW{
	SCROLLINFO scr;
public:
	MYWINDOW(int w, int h) : WINDOW(w, h){}
	MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
	MYWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){}
	~MYWINDOW(){}
	
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBox(hwnd, "end", "Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DEBUG::DebugConsole::Get_Instance().Init();
	
	
	//AZ::GUI::WINDOW::UseUnicode(false);
	MYWINDOW mw(500, 500, L"First");
	
	mw.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MainWindow").Register();
	
	mw.Create();
	mw.Show(nCmdShow);
	return mw.Message();
}