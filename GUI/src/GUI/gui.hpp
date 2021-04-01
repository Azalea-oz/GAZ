#pragma once

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
#include<algorithm>


#include"../DEBUG/AzDebug.hpp"
#include"../defines.hpp"
#include"../WCLASS/wclass.hpp"
#include"../PAINT/paint.hpp"
#include"../EVENT/event.hpp"
#include"../UTIL/utility.hpp"

#define WINDOW_CHILD 0xffff

#define EBREAK (0)
#define ECALL (1)


namespace AZ{
	namespace GUI{
		typedef int CODE;
		
		class WINDOW;
		
		class PROCMAP : public UTIL::Singleton<PROCMAP>{
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
			
			void InitWindowClass();
			void InitFrameRate(int);
			
			//function pointer
			using WPROC = LRESULT (WINDOW::*)(HWND, UINT, WPARAM, LPARAM);
			WPROC Proc;
			static LRESULT CALLBACK EntryProcA(HWND, UINT, WPARAM, LPARAM);
			static LRESULT CALLBACK EntryProcW(HWND, UINT, WPARAM, LPARAM);
			
		public:
			//window class option
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
			
			//register window
			WINDOW& Register();
			
			LRESULT MyProc(HWND, UINT, WPARAM, LPARAM);
			
			//state of option
			// Is using UNICODE?
			// Is using Double Buffering?
			// Is using Reative Sizing?
			// Is using Double click?
			/*
			class MODE{
				WINDOW *_pWindow; //???
				bool _Unicode;
				bool _DBuff;
				bool _RelativeSize;
				bool _DClick;
			public:
				MODE(WINDOW*);
				~MODE();
				void EnableUnicode(const bool);
				void EnableDBuff(const bool);
				void EnableRelativeSize(const bool);
				void EnableDClick(const bool);
				
				bool isUnicode();
				bool isDBuff();
				bool isRelativeSize();
				bool isDClick();
				
			} Mode;
			*/
			class MODE{
				WINDOW *wp;
				bool state;
			public:
				MODE(WINDOW*);
				MODE(WINDOW*, bool);
				~MODE();
				
				void Enable(bool);
				bool is();
			} Unicode, DBuff, DBuffDIB, DClick, AutoReSize;
			
		protected:
			const WNDCLASSEX GetWcex();
			
			
			
		// TITLE
		protected:
			std::string _Title;
			std::wstring _TitleW;
			
			/*
			std::string _Menu;
			std::wstring _MenuW;
			*/
			
		public:
			WINDOW& SetTitle(const std::string);
			WINDOW& SetTitle(const std::wstring);
			
			std::string GetTitleA();
			std::wstring GetTitleW();
			
			bool ChangeTitle(const std::string);
			bool ChangeTitle(const std::wstring);
			
			/*
			WINDOW& SetMenu(const std::string);
			WINDOW& SetMenu(const std::wstring);
			
			std::string GetMenuA();
			std::wstring GetMenuW();
			
			bool ChangeMenu(const std::string);
			bool ChangeMenu(const std::wstring);
			*/
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
			WINDOW(const int, const int, const std::string, const std::string);
			WINDOW(const int, const int, const std::wstring);
			WINDOW(const int, const int, const std::wstring, const std::wstring);
			WINDOW(const std::string);
			WINDOW(const std::string, const std::string);
			WINDOW(const std::wstring);
			WINDOW(const std::wstring, const std::wstring);
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
			void Child(bool);
			bool isChild();
			
			void SetMenuId(const HMENU);
			
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
			static MOUSE _mouse;
			
		private:
			bool RegisterFlag;
			WNDPROC DefProc;
			//LRESULT CALLBACK (*CallProc)(HWND, UINT, WPARAM, LPARAM);
			void InitCodeArray();
		protected:
			
			
			void ESetProc();
			std::array<CODE (WINDOW::*)(const HWND, const UINT, const WPARAM, const LPARAM), 24> CodeFuncArray;
			
			CODE _ESIZE(const HWND, const UINT, const WPARAM, const LPARAM);
			
			// virtual event function
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
			virtual CODE ECLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EDCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMDOWN(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMUP(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EHOLD(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EPAINT(const HWND, const UINT, const WPARAM, const LPARAM, HDC);
			LRESULT CALLBACK EBack(const HWND, const UINT, const WPARAM, const LPARAM);
			
			// ここら辺はきれいにしたい
			virtual CODE CustomMsg(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _CHILDMSG(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE CHILDMSG(const HWND, const UINT, const WPARAM, const LPARAM);
			
			// 緩衝材
			CODE _EVENT(const HWND, const UINT, const WPARAM, const LPARAM,
				CODE (WINDOW::*)(const HWND, const UINT, const WPARAM, const LPARAM),
				CODE (WINDOW::*)(const HWND, const UINT, const WPARAM, const LPARAM));
			CODE _ECREATE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ECLOSE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EDESTROY(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ECOMMAND(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMOUSE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMDI(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ENCDESTROY(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ENCHITTEST(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ENCMOUSE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EEDIT(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ECHAR(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EKEY(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EQUIT(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ESCROLL(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EACTIVE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EFOCUS(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMOVE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ETEXT(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMENU(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EITEM(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ETIMER(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ESTATE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EFILE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EBKG(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ERELATIVESIZE(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ECLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EDCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMDOWN(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMUP(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EHOLD(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EPAINT(const HWND, const UINT, const WPARAM, const LPARAM);
			//std::vector< void(*)(HDC) > Layer;
			
			
		//ラムダ関数群
		public:
			void Layout(CODE (*LayoutFunc)(HDC));
			void GameLoop(void (*_GameLoop)(LPVOID), LPVOID);
			void RegMsgCode(std::function< CODE(const HWND, const UINT, const WPARAM, const LPARAM) >, UINT _msg);
			void Wait(void (*_Waitp)(LPVOID), LPVOID);
		private:
			std::function< int(HDC) > LayoutFuncP;
			std::function< void(LPVOID) > _GameLoopP;
			LPVOID GameLoopArgs;
			std::function< void(LPVOID) > _WaitP;
			LPVOID WaitArgs;
			
			CODE (WINDOW::*evep)(const HWND, const UINT, const WPARAM, const LPARAM);
			
			void InitLambda();
		private:
			long long WaitToNextTime;
			int FrameRate;
			
			static std::function<long long(void)> CurrentTimeMicro;
			static std::function<long long(void)> CurrentTimeMilli;
		public:
			void FPSLock(int);
			void Wait();
			long long _wait;
			long long _now;
			
		//デバッグ
		public:
			void Print();
			
			long long GetWait();
			long long GetNow();
			long long GetNext();
		};
	}
}