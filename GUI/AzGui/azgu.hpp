#ifndef __AZGU_HPP__
#define __AZGU_HPP__

#include<windows.h>
#include<commctrl.h>
#include<string>
#include<array>
#include"../DEBUG/AzDebug.hpp"

#define ID_BUTTON 10000
#define IDM_END   10001
#define IDM_ON    10002
#define IDM_OFF   10003

namespace AZ{
	namespace GUI{
		namespace WINDOW{
			class POS{
				std::array<int, 2> Pos;
			public:
				POS();
				POS(int, int);
				~POS();
				int X();
				int Y();
				void Set(int, int);
				std::array<int, 2> Get();
			};
			class SIZE{
				std::array<int, 2> Size;
			public:
				SIZE();
				SIZE(int, int);
				~SIZE();
				int Width();
				int Height();
				void Set(int, int);
				std::array<int, 2> Get();
			};
			class STATE{
				HWND hwnd;
				SIZE size;
				POS pos;
				
			public:
				STATE();
				STATE(int, int);
				~STATE();
				
				void SetPos(int, int);
				void SetSize(int, int);
				std::array<int, 2> GetSize();
				std::array<int, 2> GetPos();
			};
			class AZWCL{
				WNDCLASSEX wcex;
				static AZWCL* tmp;
				
				UINT cbSize;
				UINT style;
				WNDPROC lpfnWndProc;
				int cbClsExtra;
				int cbWndExtra;
				HINSTANCE hInstance;
				HICON hIcon;
				HICON hIconSm;
				HCURSOR hCursor;
				HBRUSH hbrBackground;
				std::string lpszMenuName;
				std::string lpszClassName;
				
				DEBUG::DebugConsole *Debug;
				
				AZWCL *GetInst();
				
				
				
				
				
				//仮想ウィンドウプロシージャ―
				//この行(コメントアウト)を消すな
				virtual LRESULT AZPROC(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
				//プロシージャ―のエントリーポイント
				static LRESULT CALLBACK entryProc(HWND, UINT, WPARAM, LPARAM);
				
			public:
				AZWCL(HINSTANCE hinstance);
				~AZWCL();
				
				void Init(HINSTANCE hinstance);
				
				AZWCL *SetClass();
				AZWCL *Size(UINT);
				AZWCL *Style(UINT);
				AZWCL *WndProc(WNDPROC);
				AZWCL *ClsExtra(int);
				AZWCL *WndExtra(int);
				AZWCL *Instance(HINSTANCE);
				AZWCL *Icon(HICON);
				AZWCL *IconSm(HICON);
				AZWCL *Cursor(HCURSOR);
				AZWCL *Background(HBRUSH);
				AZWCL *MenuName(std::string);
				AZWCL *ClassName(std::string);
				
				std::string GetClassName();
				AZWCL *Register();

				const WNDCLASSEX GetWcex();
				void Print();
				void Print(const WNDCLASSEX);
				void UseDebug(bool);
			};
			
			class AZWINDOW : protected STATE{
				AZWCL wcl;
				std::string title;
				HWND hwnd;
				HINSTANCE hinst;
				MSG msg;
				
			public:
				AZWINDOW();
				AZWINDOW(int, int);
				AZWINDOW(int, int, std::string);
				AZWINDOW(std::string);
				~AZWINDOW();
				
				void Create();
				void Create(std::string);
				AZWCL *SetClass();
				
				HWND GetHandle();
				
				int Message();
				void Show(int);
				
				void UseDebug(bool);
			};
		}
		namespace CTRL{
			class CTRLOR : protected WINDOW::STATE{};
			class LIST : protected CTRLOR{};
			class BUTTON : protected CTRLOR{};
			class DIALOG : protected CTRLOR{};
			class PROGRESS_BAR  : protected CTRLOR{};
		}
		namespace PAINT{}
	}
	namespace FILE{}
	namespace DISC{}
	namespace DIRECTRY{}
	namespace MEMORY{}
	namespace SYSTEM{}
	namespace PROCESS{}
	namespace MOUSE{}
	namespace KEYBOARD{}
	namespace REGIST{}
	
	class AzMenu{};
	class AzWindow_State{
		std::string Window_title;
		
	};
	
}

#endif