#include<windows.h>
#include<tchar.h>
#include<string>

#define UNICODE

#define DEBUG(x) MessageBox(NULL, x, "DEBUG", MB_OK)

void ERR(HWND hwnd){
	DWORD ErrCode = GetLastError();
	LPVOID lpMsgBuf;
	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, ErrCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf, 0, NULL);
	
	MessageBoxW(hwnd, (LPCWSTR)lpMsgBuf, L"error", MB_OK);
	LocalFree(lpMsgBuf);
}

LRESULT CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (msg) {
	case WM_CREATE:
		
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd , &ps);
		
		// ---paint---
		
		// -----------
		
		EndPaint(hwnd , &ps);
		return 0;
	}
	
	return DefWindowProcW(hwnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nCmd){
	HWND hwnd;
	//HACCEL haccel;
	MSG msg;
	WNDCLASSEXW wc;
	
	
	std::wstring ClassName = L"template";
	std::wstring Title = L"あいうえお";
	
	LPTSTR err;

	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	if(!RegisterClassExW(&wc)){
		DEBUG("ERROR:RegistClass");
		return 0;
	}

	hwnd = CreateWindowExW(
		0, (LPCWSTR)ClassName.c_str(),
		(LPCWSTR)Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);
	if (!hwnd){
		//DEBUG("ERROR:CreateWindow");
		ERR(NULL);
		return 0;
	}
	
	ShowWindow(hwnd, nCmd);
	UpdateWindow(hwnd);
	
	//haccel = LoadAccelerators(hInst, TEXT("KITTY"));
	
	while (GetMessageW(&msg, NULL, 0, 0)) {
		//if(!TranslateAcceleratorW(hwnd, , &msg)){
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		//}
	}
	
	return msg.wParam;
}