#ifndef __GUI_HPP__
#define __GUI_HPP__

#include<windows.h>
#include<gdiplus.h>
#include<commctrl.h>
#include<string>
#include<vector>
#include<iostream>
#include<cstdio>
#include<array>
#include<map>
#include<thread>
#include<chrono>
#include<functional>

#include"../DEBUG/AzDebug.hpp"
#include"../defines.hpp"
#include"../WCLASS/wclass.hpp"
#include"../PAINT/paint.hpp"
#include"../EVENT/event.hpp"

#define WINDOW_CHILD 0xffff

#define EBREAK (0)
#define ECALL (1)


namespace AZ{
	namespace GUI{
		typedef int CODE;
		
		class WINDOW;
		
		class PROCMAP : public SINGLETON::Singleton<PROCMAP>{
			std::map<HWND, WINDOW*> hWndMap;
		public:
			PROCMAP();
			~PROCMAP();
			WINDOW* find(HWND);
			bool Register(HWND, WINDOW*);
			bool Remove(HWND);
			
			void DebugPrint();
			
		};
		
		
		
		class WINDOW : public STATE{
			WNDCLASSEX wcex;
			WNDCLASSEXW wcexw;
			static WINDOW* tmp;
			
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
			std::wstring lpszMenuNameW;
			std::string lpszClassName;
			std::wstring lpszClassNameW;
			
			//function pointer
			using WPROC = LRESULT (WINDOW::*)(HWND, UINT, WPARAM, LPARAM);
			WPROC Proc;
			static LRESULT CALLBACK EntryProc(HWND, UINT, WPARAM, LPARAM);
			static LRESULT CALLBACK EntryProcW(HWND, UINT, WPARAM, LPARAM);
			
		public:
			WINDOW& WClassSize(const UINT);
			WINDOW& WClassStyle(const UINT);
			WINDOW& WClassWndProc(WNDPROC);
			WINDOW& WClassClsExtra(const int);
			WINDOW& WClassWndExtra(const int);
			WINDOW& WClassInstance(const HINSTANCE);
			WINDOW& WClassIcon(HICON);
			WINDOW& WClassIconSm(HICON);
			WINDOW& WClassCursor(HCURSOR);
			WINDOW& WClassBackground(const HBRUSH);
			WINDOW& WClassMenuName(const std::string);
			WINDOW& WClassMenuName(const std::wstring);
			WINDOW& WClassName(const std::string);
			WINDOW& WClassName(const std::wstring);
			
			std::string GetClassNameA();
			std::wstring GetClassNameW();
			
			WINDOW& Register();
			
			LRESULT MyProc(HWND, UINT, WPARAM, LPARAM);
			
			
			class MODE{
				WINDOW *_pWindow;
				bool _Unicode;
				bool _DBuff;
				bool _RelativeSize;
			public:
				MODE(WINDOW*);
				~MODE();
				void Unicode(const bool);
				void DBuff(const bool);
				void RelativeSize(const bool);
				
				bool isUnicode();
				bool isDBuff();
				bool isRelativeSize();
			} Mode;
			
		protected:
			const WNDCLASSEX GetWcex();
			
			
			
		// TITLE
		protected:
			std::string _Title;
			std::wstring _TitleW;
			
		public:
			WINDOW& SetTitle(const std::string);
			WINDOW& SetTitle(const std::wstring);
			
			std::string GetTitleA();
			std::wstring GetTitleW();
			
			bool ChangeTitle(const std::string);
			bool ChangeTitle(const std::wstring);
			
		// STYLE
		protected:
			DWORD _ExStyle;
			DWORD _WindowStyle;
			
		public:
			WINDOW& SetExStyle(const DWORD);
			WINDOW& SetWindowStyle(const DWORD);
			
			DWORD GetExStyle();
			DWORD GetWindowStyle();
			
		protected:
			HWND hwnd;
			HWND hparent;
			MSG msg;
			HINSTANCE hinst;
			HMENU Menu;
			
			std::vector<std::pair<HMENU, WINDOW*> > ChildWindow;
			bool Border;
		public:
			WINDOW();
			WINDOW(const int, const int);
			WINDOW(const int, const int, const std::string);
			WINDOW(const int, const int, const std::wstring);
			WINDOW(const std::string);
			WINDOW(const std::wstring);
			virtual ~WINDOW();
			
			WINDOW& WindowSize(const int, const int);
			WINDOW& WindowPos(const int, const int);
			
			
			WINDOW& Borderless();
			
			HINSTANCE GetInst();
			
			void ResizeClient();
			void ReSizeWindow(const int, const int);
			
			void Create();
			void Create(const std::string);
			void Create(const std::wstring);
			
			void Child(WINDOW&, const HMENU);
			void SetMenu(const HMENU);
			
			LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);
			using PROC = LRESULT (*)(HWND, UINT, WPARAM, LPARAM);
			
			PROC CustomProc;
			
			int Message();
			void Show(const int);
			bool Enable(const bool);
			
			HWND GetHandle();
			HWND GetParentHandle();
			
		private:
			WINDOW *Parent;
			
		public:
			void SetParent(WINDOW*);
			WINDOW& GetParent();
		protected:
			void SetHandle(const HWND);
			void SetParentHandle(const HWND);
			
			
			
			
		private:
			bool RegisterFlag;
			WNDPROC DefProc;
			//LRESULT CALLBACK (*CallProc)(HWND, UINT, WPARAM, LPARAM);
			void InitCodeArray();
		protected:
			
			
			void ESetProc();
			std::array<CODE (WINDOW::*)(const HWND, const UINT, const WPARAM, const LPARAM), 24> CodeFuncArray;
			
			void _ESIZE(const HWND, const UINT, const WPARAM, const LPARAM);
			
			virtual CODE ECREATE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ECLOSE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EDESTROY(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ECOMMAND(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMOUSE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMDI(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ENCDESTROY(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ENCHITTEST(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ENCMOUSE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EEDIT(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ECHAR(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EKEY(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EQUIT(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ESCROLL(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EACTIVE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EFOCUS(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMOVE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ESIZE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ETEXT(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMENU(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EITEM(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ETIMER(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ESTATE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EFILE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EBKG(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ERELATIVESIZE(const HWND, const UINT, const WPARAM, const LPARAM);
			LRESULT CALLBACK EBack(const HWND, const UINT, const WPARAM, const LPARAM);
			
			virtual CODE CustomMsg(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE UNIQMSG(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EVENT(const HWND, const UINT, const WPARAM, const LPARAM);
			
			CODE _EPAINT(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EPAINT(const HWND, const UINT, const WPARAM, const LPARAM);
			//std::vector< void(*)(HDC) > Layer;
			
		//ラムダ関数群
		public:
			void Layout(CODE (*LayoutFunc)(HDC));
			void GameLoop(void (*_GameLoop)(LPVOID), LPVOID);
			void RegMsgCode(std::function< CODE(const HWND, const UINT, const WPARAM, const LPARAM) >, UINT _msg);
		private:
			std::function< int(HDC) > LayoutFuncP;
			std::function< void(LPVOID) > _GameLoopP;
			LPVOID GameLoopArgs;
			
		private:
			long long WaitToNextTime;
			int FrameRate;
			
			static std::function<long long(void)> CurrentTimeMicro;
		public:
			void FPSLock(int);
			void Wait();
			
		//デバッグ
		public:
			void Print();
		};
	}
}

#endif