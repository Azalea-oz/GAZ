#define _WIN32_IE 0x0500

#include <windows.h>
#include <shellapi.h>
#include <stdio.h>

#define PROGRAM_NAME    "BalloonTest"
#define MY_NOTIFYICON   (WM_APP + 100)
#define IDC_BUTTON  0

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow);
HWND InitWindow (void);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInstance;

////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow) {
    MSG msg;
    BOOL bRet;
    g_hInstance = hInstance;
    InitWindow();
    while ( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0 ) {
        if (bRet == -1) {
            MessageBox(0, "handle the error and possibly exit", "error", MB_ICONSTOP);
            break;
        } else {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }
    return msg.wParam;
}

HWND InitWindow (void) {
    HWND hWnd;
    WNDCLASSEX wcex;

    ZeroMemory((LPVOID)&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = g_hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0,0,0));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = PROGRAM_NAME;
    wcex.hIconSm = NULL;
    RegisterClassEx(&wcex);

    hWnd=CreateWindowEx(
        0,
        PROGRAM_NAME,
        PROGRAM_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        g_hInstance,
        NULL
    );

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return hWnd;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    NOTIFYICONDATA nid;
    
    switch (message) {
        case WM_CREATE:
            ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
            nid.cbSize = sizeof(NOTIFYICONDATA);
            nid.hWnd = hwnd;
            nid.uID = 0;
            nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
            nid.uCallbackMessage = MY_NOTIFYICON;
            nid.hIcon = NULL;
            lstrcpy(nid.szTip, "∩(　´Α｀)＜　先生、「バルーンヘルプ」ってどうよ？");
            Shell_NotifyIcon(NIM_ADD, &nid);
            
            CreateWindowEx(0, "BUTTON", "バルーン始動", WS_CHILD | WS_VISIBLE, 
                0, 0, 100, 100, hwnd, NULL, g_hInstance, IDC_BUTTON);
            
            return 0;
        case WM_COMMAND:
            if ( LOWORD(wParam) == IDC_BUTTON ) {
                ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
                nid.cbSize = sizeof(NOTIFYICONDATA);
                nid.uFlags = NIF_INFO;
                nid.hWnd = hwnd;
                lstrcpy(nid.szInfoTitle, "Windowsがお亡くなりになりました");
                lstrcpy(nid.szInfo, "kara：どうしようもありませんな\nＹ嵜：所詮winだからな");
                nid.dwInfoFlags = 3;
                Shell_NotifyIcon(NIM_MODIFY, &nid);
            }
            return 0;
        case MY_NOTIFYICON:
            return 0;
        case WM_CLOSE:
            ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
            nid.cbSize = sizeof(NOTIFYICONDATA);
            nid.hWnd = hwnd;
            Shell_NotifyIcon(NIM_DELETE, &nid);
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hwnd,message,wParam,lParam));
    }
    return 0L;
}