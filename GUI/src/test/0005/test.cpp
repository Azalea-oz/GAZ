#include<windows.h>
#include<iostream>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch(msg){
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		
		hdc = BeginPaint(hwnd, &ps);
		
		Rectangle(hdc , 0 , 0 , 200, 200);
		LineTo(hdc, 200, 200);
		MoveToEx(hdc, 0, 200, NULL);
		LineTo(hdc, 200, 0);
		
		EndPaint(hwnd, &ps);
		return 0L;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd, chwnd;
	MSG msg;
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL , IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "TEST";
	wcex.hIconSm = LoadIcon(NULL , IDI_APPLICATION);
	
	RegisterClassEx(&wcex);
	
	hwnd = CreateWindowEx(
		0, "TEST", "TEST WINDOW",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 400, 400,
		NULL, NULL, hInstance, NULL);
	
	hwnd = CreateWindowEx(
		0, "TEST", "CHILD WINDOW",
		WS_CHILD | WS_VISIBLE, 200, 200, 200, 200,
		hwnd, NULL, hInstance, NULL);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	ShowWindow(chwnd, nCmdShow);
	UpdateWindow(chwnd);
	
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return (int)msg.wParam;
}