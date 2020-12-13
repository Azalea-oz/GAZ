#ifndef STRICT
#define STRICT
#endif
#define ID_EDIT 100
#include<windows.h>
#include<imm.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK NewEditProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

char szClassName[] = "ime01";    //�E�B���h�E�N���X
WNDPROC OrgEditProc; //���X�̃G�f�B�b�g�R���g���[���̃v���V�[�W��

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
                   LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
    
    if (!InitApp(hCurInst))
        return FALSE;
    if (!InitInstance(hCurInst, nCmdShow)) 
        return FALSE;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

//�E�B���h�E�E�N���X�̓o�^

ATOM InitApp(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;    //�v���V�[�W����
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;//�C���X�^���X
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "MYMENU";    //���j���[��
    wc.lpszClassName = (LPCSTR)szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    return (RegisterClassEx(&wc));
}

//�E�B���h�E�̐���

BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(szClassName,
            "�L�ł��킩��IME", //�^�C�g���o�[�ɂ��̖��O���\������܂�
            WS_OVERLAPPEDWINDOW, //�E�B���h�E�̎��
            CW_USEDEFAULT,    //�w���W
            CW_USEDEFAULT,    //�x���W
            CW_USEDEFAULT,    //��
            CW_USEDEFAULT,    //����
            NULL, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
            NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
            hInst, //�C���X�^���X�n���h��
            NULL);
    if (!hWnd)
        return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}


//�E�B���h�E�v���V�[�W��

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int id;
    static HWND hEdit;
    HINSTANCE hInst;
    static HKL hKl;
    REGISTERWORD rw;
    char szBuf[256] = "", *lpszText;
    HGLOBAL hMem;
    DWORD dwStart, dwEnd, dwLen;
    DWORD i;


    switch (msg) {
        case WM_CREATE:
            hInst = (HINSTANCE)(((CREATESTRUCT *)lp)->hInstance);
            hEdit = CreateWindowEx(0,
                "Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_WANTRETURN,
                0, 0, 0, 0, hWnd, (HMENU)ID_EDIT, hInst, NULL);
            SetFocus(hEdit);
    		OrgEditProc = (WNDPROC)GetWindowLong(hEdit, GWLP_WNDPROC);
            SetWindowLong(hEdit, GWLP_WNDPROC, (LONG)NewEditProc);
            hKl = GetKeyboardLayout(0);
            break;
        case WM_SIZE:
            MoveWindow(hEdit, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
            break;
        case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
                case IDM_IMEDLG:
                    ImmConfigureIME(hKl, hEdit, IME_CONFIG_GENERAL, NULL);
                    SetFocus(hEdit);
                    break;
                case IDM_REGIST:
                    SendMessage(hEdit, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
                    if (dwStart != dwEnd) {
                        dwLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                        hMem = GlobalAlloc(GHND, dwLen + 1);
                        if (hMem == NULL) {
                            MessageBox(hWnd, "���������m�ۂł��܂���", "Error", MB_OK);
                            return 0;
                        }
                        lpszText = (char *)GlobalLock(hMem);
                        GetWindowText(hEdit, lpszText, dwLen + 1);
                        SendMessage(hEdit, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
                        for (i = 0; i <= dwEnd - dwStart - 1; i++) {
                            szBuf[i] = lpszText[dwStart + i];
                        }
                        GlobalUnlock(hMem);
                        GlobalFree(hMem);
                    } 
                    rw.lpReading = NULL;
                    rw.lpWord = szBuf;
                    ImmConfigureIME(hKl, hEdit, IME_CONFIG_REGISTERWORD, &rw);
                    SetFocus(hEdit);
                    break;
            }
            break;
        case WM_CLOSE:
            id = MessageBox(hWnd,
                "�I�����Ă��悢�ł���",
                "�I���m�F",
                MB_YESNO | MB_ICONQUESTION);
            if (id == IDYES) {
                SetWindowLong(hEdit, GWLP_WNDPROC, (LONG)OrgEditProc);
                DestroyWindow(hEdit);
                DestroyWindow(hWnd);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0;
}

LRESULT CALLBACK NewEditProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HIMC hImc;
    switch (msg) {
        case WM_CHAR:
            if (wp == (WPARAM)0x1b) {
                hImc = ImmGetContext(hWnd);
                if (ImmGetOpenStatus(hImc)) {
                    ImmSetOpenStatus(hImc, FALSE);
                } else {
                    ImmSetOpenStatus(hImc, TRUE);
                }
                if (ImmReleaseContext(hWnd, hImc) == 0)
                    MessageBox(hWnd, "ImmReleaseContext Error", "Error", MB_OK);
                return 0;
            }
        default:
            break;
    }
    return CallWindowProc(OrgEditProc, hWnd, msg, wp, lp);
}