#include"Azgui.h"

class MainWindow : public Az::AzWindow {
public:
	MainWindow(LPCSTR);
	~MainWindow();
	LRESULT AzWndProc(HWND, UINT, WPARAM, LPARAM);
};

class OtherWindow : public Az::AzWindow {
public:
	OtherWindow(LPCSTR);
	~OtherWindow();
	LRESULT AzWndProc(HWND, UINT, WPARAM, LPARAM);
};