#include"Azgui.h"

namespace Az {
	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	pos::pos() {
		SetSize(10, 10);
		SetLocation(100, 100);
	}
	pos::pos(const int X, const int Y, const int Width, const int Height) {
		SetSize(X, Y);
		SetLocation(Width, Height);
	}
	void pos::SetSize(const int X, const int Y) {
		x = X;
		y = Y;
	}

	void pos::SetLocation(const int Width, const int Height) {
		width = Width;
		height = Height;
	}

	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	AzWindow *AzWindow::tmp = NULL;

	//--------------------------------------------------------------------
	//�R���X�g���N�^
	//--------------------------------------------------------------------
	AzWindow::AzWindow() {

	}

	AzWindow::AzWindow(LPCSTR tmp_ClassName) {
		hwnd.reserve(3);
		pos.reserve(3);
		ClassName = tmp_ClassName;
	}

	//--------------------------------------------------------------------
	//�f�X�g���N�^
	//--------------------------------------------------------------------
	AzWindow::~AzWindow() {
		UnregisterClass(ClassName, GetModuleHandle(NULL));
	}

	//--------------------------------------------------------------------
	//���z�E�C���h�E�v���V�[�W���\
	//�����F      hWnd      �E�B���h�E�n���h��
	//            msg       ���b�Z�[�W
	//            wp        �p�����[�^
	//            lp        �p�����[�^
	//
	//�߂�l�F��������
	//--------------------------------------------------------------------
	LRESULT AzWindow::AzWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
		switch (msg) {
		case WM_CREATE:
			CreateMenu();
			CreateWindowEx(0, "BUTTON", "�{�^��", WS_CHILD | WS_VISIBLE, 30, 30, 80, 40, hWnd, (HMENU)ID_BUTTON, ((LPCREATESTRUCT)lp)->hInstance, NULL);

			return 0;
		case WM_PAINT:
			AzWndPaint(hWnd);
			return 0;
		case WM_SIZE:
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		case WM_COMMAND:
			switch (LOWORD(wp)) {
			case ID_BUTTON:
				MessageBox(NULL, "��������", "���b�Z�[�W�{�b�N�X", MB_OK);
				return 0;
			case IDM_END:
				MessageBox(NULL, "��������", "���b�Z�[�W�{�b�N�X", MB_OK);
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				return 0;
			case IDM_ON:
				return 0;
			case IDM_OFF:
				return 0;
			}
			break;
		case WM_CLOSE:
			if (IDYES == MessageBox(hWnd, "����`���`�H", "Confirmation", MB_YESNO)) {
				DestroyWindow(hWnd);
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wp, lp);
	}

	//--------------------------------------------------------------------
	//�E�C���h�E�v���V�[�W���\�̃G���g���[�|�C���g
	//�����F      hWnd      �E�B���h�E�n���h��
	//            msg       ���b�Z�[�W
	//            wp        �p�����[�^
	//            lp        �p�����[�^
	//
	//�߂�l�F��������
	//--------------------------------------------------------------------
	LRESULT CALLBACK AzWindow::entryProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
		AzWindow* pw = (AzWindow*)(LONG_PTR)GetWindowLong(hWnd, GWL_USERDATA);
		//this�|�C���^���擾�ł����ꍇ
		if (pw != NULL) {
			// �{���̃E�B���h�E�v���V�[�W�����Ăяo�����b�Z�[�W��������
			LRESULT lResult = pw->AzWndProc(hWnd, msg, wp, lp);
			return lResult;
		}

		//this�|�C���^���擾�ł��Ȃ������ꍇ
		else {
			// �E�B���h�E�̍쐬���̏ꍇ
			if (msg == WM_CREATE || msg == WM_INITDIALOG) {
				// �v���p�e�B���X�g�ɃI�u�W�F�N�g�|�C���^(this�|�C���^)��ݒ肷��
				SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)(LONG_PTR)(tmp));
				// ���������b�Z�[�W�̍đ��M
				SendMessage(hWnd, msg, wp, lp);

				tmp = NULL;	// �o�^�����̂ňꎞ�C���X�^���X�|�C���^�i�[�̉���
			}
		}

		return DefWindowProc(hWnd, msg, wp, lp);
	}

	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	void AzWindow::AzWndPaint(HWND hWnd) {
		//�`���n��
		this->hdc = BeginPaint(hWnd, &(this->ps));
		GetClientRect(hWnd, &(this->rect));

		DrawText(hdc, "Hello World", -1, &rect, DT_CENTER | DT_WORDBREAK | DT_NOPREFIX);

		//�`���I���
		EndPaint(hWnd, &(this->ps));
	}

	void AzWindow::AzWndAccelerator() {

	}

	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	void AzWindow::InitWC() {
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc = entryProc;
		wcex.cbClsExtra = wcex.cbWndExtra = 0;
		wcex.hInstance = GetModuleHandle(NULL);
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = ClassName;
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	}

	void AzWindow::SetStyle(UINT style) {
		wcex.cbSize = style;
	}

	void AzWindow::SetCursor(LPCSTR path) {
		wcex.hCursor = (HCURSOR)LoadImage(NULL, path, IMAGE_CURSOR, 0, 0, LR_SHARED);
	}

	void AzWindow::SetIcon(LPCSTR path) {
		wcex.hIcon = (HICON)LoadImage(NULL, path, IMAGE_ICON, 0, 0, LR_SHARED);
	}

	void AzWindow::SetIconsm(LPCSTR path) {
		wcex.hIconSm = (HICON)LoadImage(NULL, path, IMAGE_ICON, 0, 0, LR_SHARED);
	}

	void AzWindow::SetBackGround(int color) {
		wcex.hbrBackground = (HBRUSH)GetStockObject(color);
	}

	void AzWindow::SetClassName(LPCSTR name) {
		ClassName = name;
	}

	void AzWindow::SetLayered() {
		ExStyle = WS_EX_LAYERED;
	}

	void AzWindow::NoMenu() {
		wcex.lpszMenuName = NULL;
	}

	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	bool AzWindow::Create(LPCSTR Title) {
		if (!RegisterClassEx(&wcex)) {
			MessageBox(NULL, GetErr(), "���b�Z�[�W�{�b�N�X", MB_OK);
			return false;
		}

		tmp = this;
		hwnd[0] = CreateWindowEx(ExStyle, ClassName, Title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			pos[0].x, pos[0].y, pos[0].width, pos[0].height,
			NULL, LoadMenu(GetModuleHandle(NULL), "Menu"), GetModuleHandle(NULL), NULL);

		if (hwnd[0] == NULL) {

			MessageBox(NULL, GetErr(), "���b�Z�[�W�{�b�N�X", MB_OK);
			return false;
		}

		ShowWindow(hwnd[0], SW_SHOW);
		UpdateWindow(hwnd[0]);

		return true;
	}

	bool AzWindow::Create(LPCSTR Title, LPCSTR Menu) {
		if (!RegisterClassEx(&wcex)) {
			MessageBox(NULL, GetErr(), "���b�Z�[�W�{�b�N�X", MB_OK);
			return false;
		}

		tmp = this;
		hwnd[0] = CreateWindowEx(ExStyle, ClassName, Title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			pos[0].x, pos[0].y, pos[0].width, pos[0].height,
			NULL, LoadMenu(GetModuleHandle(NULL), Menu), GetModuleHandle(NULL), NULL);

		if (hwnd[0] == NULL) {

			MessageBox(NULL, GetErr(), "���b�Z�[�W�{�b�N�X", MB_OK);
			return false;
		}

		ShowWindow(hwnd[0], SW_SHOW);
		UpdateWindow(hwnd[0]);

		return true;
	}

	bool AzWindow::Child(LPCSTR Title) {
		tmp = this;
		hwnd.push_back(CreateWindowEx(0, ClassName, Title, WS_CHILD | WS_VISIBLE,
			0, 0, pos.back().width - 50, pos.back().height - 50,
			hwnd[0], NULL, GetModuleHandle(NULL), NULL));

		if (hwnd.back() == NULL) {
			MessageBox(NULL, GetErr(), "���b�Z�[�W�{�b�N�X", MB_OK);
			return false;
		}

		ShowWindow(hwnd.back(), SW_SHOW);

		UpdateWindow(hwnd.back());
		return true;
	}
	
	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	void AzWindow::CreateMenu() {
		HWND hStatus;
		HMENU hMenu;
		InitCommonControls();
		hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
			WS_CHILD | SBARS_SIZEGRIP | CCS_BOTTOM | WS_VISIBLE, 0, 0, 0, 0,
			hwnd[0], (HMENU)ID_STATUS, GetModuleHandle(NULL), NULL);
		SendMessage(hStatus, SB_SIMPLE, TRUE, 0L);
		EnableMenuItem(hMenu, IDM_ON, MF_GRAYED);
	}
	
	void AzWindow::CreateButton(LPCSTR title, POS pos, HMENU id) {
		
	}
	//--------------------------------------------------------------------
	//
	//--------------------------------------------------------------------
	int AzWindow::LoopMsg() {
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.wParam;
	}

	int AzWindow::LoopFps(int fps) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {

			if (!GetMessage(&msg, NULL, 0, 0)) {
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else {
			GameEvent();
		}
		return msg.wParam;
	}

	void AzWindow::GameEvent() {

	}

	LPTSTR GetErr() {
		LPTSTR Buffer = NULL;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			LANG_USER_DEFAULT,
			(LPTSTR)&Buffer,
			0,
			NULL);

		return Buffer;
	}
	//--------------------------------------------------------------------

}


