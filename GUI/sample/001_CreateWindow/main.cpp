#include"../../src/AAAZLE.hpp"


class MAINWINDOW : public AZ::GUI::WINDOW{
	
public:
	MAINWINDOW() : WINDOW(500, 500, L"テストだにゃ(⋈◍＞◡＜◍)ｂ✧♡"){
		WClassName(L"MainWindow").Register();
		//WClassName(L"MainWindow");
	}
	~MAINWINDOW(){}
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MAINWINDOW mw;
	
	mw.Create();
	mw.ChangeTitle(L"変わったかにゃ(⋈◍＞◡＜◍)ｂ✧♡");
	
	return mw.Message();
}