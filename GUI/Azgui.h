#ifndef __AZGUI_H__
#define __AZGUI_H__

#include<windows.h>
#include<commctrl.h>
#include<vector>
#include<map>
#include"status.h"

#pragma  comment(lib, "comctl32.lib")

#define Parent 0
//use id
#define CHILD_ID     10000
#define ID_BUTTON    10001
#define BUTTON_ID2   10002
#define ID_STATUS      100

namespace Az {

	typedef struct pos {
	public:
		int x;
		int y;
		int width;
		int height;

		pos();
		pos(const int, const int, const int, const int);
		void SetSize(const int, const int);
		void SetLocation(const int, const int);
	} POS;

	//--------------------------------------------------------------------
	class AzWindow {
	private:
		std::vector<HWND> hwnd{0};
		static AzWindow *tmp;

	public:
		std::vector<POS> pos = std::vector<POS>(1);

		//コンストラクタ
		AzWindow();
		AzWindow(LPCSTR);
		//デストラクタ
		virtual ~AzWindow();

		//Windowのもろもろの設定
	private:
		WNDCLASSEX wcex;
		LPCSTR ClassName;
		MSG msg;
		DWORD ExStyle = WS_EX_TOPMOST;

	public:
		void InitWC();
		void SetStyle(UINT);
		void SetCursor(LPCSTR);
		void SetIcon(LPCSTR);
		void SetIconsm(LPCSTR);
		void SetBackGround(int);
		void SetClassName(LPCSTR);
		void SetLayered();
		void NoMenu();

		//Windowの作成
		bool Create(LPCSTR);
		bool Create(LPCSTR, LPCSTR);
		bool Child(LPCSTR);

		virtual int LoopMsg();
		int LoopFps(int);
		virtual void GameEvent();

		//プロシージャ―関係
	private:
		//仮想ウィンドウプロシージャ―
		virtual LRESULT AzWndProc(HWND, UINT, WPARAM, LPARAM);
		//プロシージャ―のエントリーポイント
		static LRESULT CALLBACK entryProc(HWND, UINT, WPARAM, LPARAM);

		//PAINT
		virtual void AzWndPaint(HWND);
		//ACCELERATOR
		virtual void AzWndAccelerator();

		PAINTSTRUCT ps;
		HDC hdc;
		RECT rect;

	public:
		//コントロール
		void CreateMenu();
		void CreateButton(LPCSTR, POS, HMENU);
	};

	LPTSTR GetErr();

	//--------------------------------------------------------------------
	
	//--------------------------------------------------------------------

}
#endif