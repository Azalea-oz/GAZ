//      ウィンドウを開く
//      Visual C++ 2013 32/64bit

#include <windows.h>
#include <tchar.h>

//      ウィンドウプロシージャー
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = TEXT("line");

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInst, TCHAR* lpszCmdLine, int nCmdShow){
        HWND hWnd;
        MSG lpMsg;
        WNDCLASS wc;

        if (!hPreInst) {
                wc.style = CS_HREDRAW | CS_VREDRAW;
                wc.lpfnWndProc = WndProc;
                wc.cbClsExtra = 0;
                wc.cbWndExtra = 0;
                wc.hInstance = hInstance;
                wc.hIcon = NULL;
                wc.hCursor = LoadCursor(NULL, IDC_ARROW);
                wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
                wc.lpszMenuName = NULL;
                wc.lpszClassName = szClassName;
                if (!RegisterClass(&wc))
                        return FALSE;
        }
        hWnd = CreateWindow(szClassName,
                _TEXT("タイトル"),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                hInstance,
                NULL);
        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);
        while (GetMessage(&lpMsg, NULL, 0, 0)) {
                TranslateMessage(&lpMsg);
                DispatchMessage(&lpMsg);
        }
        return int(lpMsg.wParam);
}

//      ウィンドウプロシージャー

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
        HDC hdc;
        PAINTSTRUCT ps;
        TCHAR* buf = TEXT("CreateWindowのサンプルプログラム");

        switch (msg) {
        case WM_DESTROY:
                PostQuitMessage(0);
                break;
        case WM_PAINT:{
                hdc = BeginPaint(hWnd, &ps);

                TextOut(hdc, 0, 0, buf, (int)_tcslen(buf));

                EndPaint(hWnd, &ps);
                break;
        }
        default:
                return(DefWindowProc(hWnd, msg, wParam, lParam));
        }
        return (0L);
}