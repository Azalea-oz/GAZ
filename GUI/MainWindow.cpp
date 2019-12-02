#include"Azgui.h"
#include"MainWindow.h"

MainWindow::MainWindow(LPCSTR tmp_ClassName) : AzWindow(tmp_ClassName) {
	pos[0].SetSize(100, 100);
	pos[0].SetLocation(500, 500);
}

MainWindow::~MainWindow(){

}

LRESULT MainWindow::AzWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE:
		InitCommonControls();
		CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)ID_STATUS, GetModuleHandle(NULL), NULL);
		CreateWindowEx(0, "BUTTON", "ボタン", WS_CHILD | WS_VISIBLE, 30, 30, 80, 40, hWnd, (HMENU)ID_BUTTON, ((LPCREATESTRUCT)lp)->hInstance, NULL);

		break;
	case WM_PAINT:
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case ID_BUTTON:
			MessageBox(NULL, "ゲーテ", "メッセージボックス", MB_OK);
			break;
		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		case IDM_ON:
			return 0;
		case IDM_OFF:
			return 0;
		}
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hWnd, "しゅ～りょ～？", "Confirmation", MB_YESNO)) {
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}

OtherWindow::OtherWindow(LPCSTR tmp_ClassName) : AzWindow(tmp_ClassName) {

}

OtherWindow::~OtherWindow() {

}

LRESULT OtherWindow::AzWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE:
		CreateWindowEx(0, "BUTTON", "ボタン", WS_CHILD | WS_VISIBLE, 30, 30, 80, 40, hWnd, (HMENU)ID_BUTTON, ((LPCREATESTRUCT)lp)->hInstance, NULL);
		CreateWindowEx(0, "BUTTON", "ボタン", WS_CHILD | WS_VISIBLE, 30, 80, 80, 40, hWnd, (HMENU)ID_BUTTON, ((LPCREATESTRUCT)lp)->hInstance, NULL);

		break;
	case WM_PAINT:
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case ID_BUTTON:
			MessageBox(NULL, "ゲーテ", "メッセージボックス", MB_OK);
			break;
		}
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hWnd, "しゅ～りょ～？", "Confirmation", MB_YESNO)) {
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}