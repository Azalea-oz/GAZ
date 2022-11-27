
//#define UNICODE
#include"../../src/AAAZLE.hpp"

#define WM_TASKTRAY (WM_USER+1)
#define ID_TASKTRAY 0

#define WIDE_MODE

class MYWINDOW : public AZ::GUI::WINDOW{
public:
	MYWINDOW(int w, int h) : WINDOW(w, h){}
	MYWINDOW(int w, int h, std::string str) : WINDOW(w, h, str){}
	MYWINDOW(int w, int h, std::wstring str) : WINDOW(w, h, str){}
	~MYWINDOW(){}

	AZ::GUI::CODE ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		#ifdef WIDE_MODE
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"Toast Notification -WideMode");
		#else
		DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"Toast Notification");
		#endif
		return 1;
	}
	AZ::GUI::CODE ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		int result = MessageBoxA(hwnd, "end", "Confirmation", MB_YESNO);
		if (IDYES != result) return 0;
		return 1;
	}
	
	AZ::GUI::CODE EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		
		Rectangle(hdc , 0 , 0 , GetSize()[0], GetSize()[1]);
		LineTo(hdc, GetSize()[0], GetSize()[1]);
		MoveToEx(hdc, 0, GetSize()[1], NULL);
		LineTo(hdc, GetSize()[0], 0);
		
		EndPaint(hwnd, &ps);
		return 1;
	}
};

class MYNOF : public AZ::GUI::WINDOW{
	#ifdef WIDE_MODE
	NOTIFYICONDATAW nid;
	#else
	NOTIFYICONDATA nid;
	#endif
	
public:
	MYNOF() : WINDOW(){}
	MYNOF(std::string str) : WINDOW(10, 10, str){}
	MYNOF(std::wstring str) : WINDOW(10, 10, str){
		WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MYNOF").Register();
		SetWindowStyle(WS_CHILD | WS_VISIBLE).WindowPos(0, 0);
		
		#ifdef WIDE_MODE
		nid.cbSize=sizeof(NOTIFYICONDATAW);
		#else
		nid.cbSize=sizeof(NOTIFYICONDATA);
		#endif
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_TASKTRAY;
		nid.uID = ID_TASKTRAY;
		nid.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		
		#ifdef WIDE_MODE
		std::wstring tmp = L"Toast Notification用\n通知領域のプログラミング\n背景色を変えたい";
		wcscpy(nid.szTip, tmp.c_str());
		#else
		std::string tmp = "Toast Notification用\n通知領域のプログラミング\n背景色を変えたい";
		lstrcpy(nid.szTip, tmp.c_str());
		#endif
	}
	~MYNOF(){
		#ifdef WIDE_MODE
		int res = Shell_NotifyIconW(NIM_DELETE, &nid);
		#else
		int res = Shell_NotifyIcon(NIM_DELETE, &nid);
		#endif
		if(res != 1) DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_WARNING, std::wstring(L"Shell_NotifyIcon return ") + std::to_wstring(res));
	}
	
	AZ::GUI::CODE ECREATE(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
		nid.hWnd = hwnd;
		
		
		#ifdef WIDE_MODE
		int res = Shell_NotifyIconW(NIM_ADD, &nid);
		#else
		int res = Shell_NotifyIcon(NIM_ADD, &nid);
		#endif
		if(res != 1) DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_WARNING, std::wstring(L"Shell_NotifyIcon return ") + std::to_wstring(res));
		return 1;
	}
	
	AZ::GUI::CODE EMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(msg){
		case WM_LBUTTONDOWN:
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Mouse L Clicked");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitleW());
			#endif
			
			nid.uFlags = NIF_INFO;
			nid.dwInfoFlags = NIIF_ERROR;
			
			#ifdef WIDE_MODE
			std::wstring tmp = L"ここにいろいろなメッセージを表示します\r\n改行もできます";
			wcscpy(nid.szInfo, tmp.c_str());
			wcscpy(nid.szInfoTitle, L"通知タイトル");
			int res = Shell_NotifyIconW(NIM_MODIFY, &nid);
			#else
			std::string tmp = "ここにいろいろなメッセージを表示します\r\n改行もできます";
			lstrcpy(nid.szInfo, tmp.c_str());
			lstrcpy(nid.szInfoTitle, "通知タイトル");
			int res = Shell_NotifyIcon(NIM_MODIFY, &nid);
			#endif
			if(res != 1) DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_WARNING, std::wstring(L"Shell_NotifyIcon return ") + std::to_wstring(res));
			
			return 1;
		}
		return 1;
	}
	AZ::GUI::CODE CustomMsg(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
		switch(msg){
		case WM_TASKTRAY:
			if(wp == ID_TASKTRAY){
				switch(lp){
				case WM_RBUTTONDOWN:
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Task tray Mouse L Clicked");
					#endif
					return 1;
				}
			}
		}
		
		
		return 1;
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DEBUG::DebugConsole::Get_Instance().Init();
	MYWINDOW mw(100, 100, L"main");
	MYNOF mynof(L"Notifycation test");
	
	
	mw.WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"MainWindow").WClassIcon(LoadIcon(NULL, IDI_QUESTION)).WClassIconSm(LoadIcon(NULL, IDI_QUESTION)).Register();
	mw.SetWindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_VSCROLL).WindowPos(0, 0);
	mw.Child(mynof, (HMENU)WM_TASKTRAY);
	
	
	mw.Create();
	
	mw.Show(nCmdShow);
	return mw.Message();
}