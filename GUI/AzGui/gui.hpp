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

#include"../DEBUG/AzDebug.hpp"
#include"defines.cpp"
#include"wclass.hpp"
#include"paint.hpp"

#define WINDOW_CHILD 0xffff




namespace AZ{
	namespace GUI{
		
		class WINDOW;
		
		class PROCMAP : public SINGLETON::Singleton<PROCMAP>{
			std::map<HWND, WINDOW*> hWndMap;
		public:
			PROCMAP();
			~PROCMAP();
			WINDOW* find(HWND);
			void Register(HWND, WINDOW*);
			void Remove(HWND);
			
		};
		
		class WINDOW : protected STATE{
			WNDCLASSEX wcex;
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
			std::string lpszClassName;
			
			
			
			//function pointer
			using WPROC = LRESULT (WINDOW::*)(HWND, UINT, WPARAM, LPARAM);
			WPROC Proc;
			static LRESULT CALLBACK EntryProc(HWND, UINT, WPARAM, LPARAM);
			
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
			WINDOW& WClassName(const std::string);
			
			std::string GetClassName();
			WINDOW& Register();
			
			LRESULT MyProc(HWND, UINT, WPARAM, LPARAM);
			
		protected:
			const WNDCLASSEX GetWcex();
		
		
		
		protected:
			std::string WTitle;
			DWORD ExStyle;
			DWORD WStyle;
			
			HWND hwnd;
			HWND hparent;
			MSG msg;
			HINSTANCE hinst;
			HMENU Menu;
			
			std::vector<WINDOW*> ChildWindow;
			
			
		public:
			WINDOW();
			WINDOW(const int, const int);
			WINDOW(const int, const int, const std::string);
			WINDOW(const std::string);
			virtual ~WINDOW();
			
			WINDOW& WindowExStyle(const DWORD);
			WINDOW& WindowStyle(const DWORD);
			WINDOW& WindowTitle(const std::string);
			WINDOW& WindowSize(const int, const int);
			WINDOW& WindowPos(const int, const int);
			
			std::string GetTitleName();
			
			void ResizeClient();
			
			void Create();
			void Create(const std::string);
			
			void Child(WINDOW&, const HMENU);
			void SetMenu(const HMENU);
			
			LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);
			using PROC = LRESULT (*)(HWND, UINT, WPARAM, LPARAM);
			
			PROC CustomProc;
			
			int Message();
			void Show(int);
		protected:
			HWND GetHandle();
			void SetHandle(HWND);
			void SetParentHandle(HWND);
			
		private:
			bool RegisterFlag;
			WNDPROC DefProc;
			//LRESULT CALLBACK (*CallProc)(HWND, UINT, WPARAM, LPARAM);
			void InitCodeArray();
		protected:
			
			using CODE = int;
			void ESetProc();
			std::array<CODE (WINDOW::*)(const HWND, const UINT, const WPARAM, const LPARAM), 24> CodeFuncArray;
			
			virtual CODE ECREATE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EPAINT(const HWND, const UINT, const WPARAM, const LPARAM);
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
			LRESULT CALLBACK EBack(const HWND, const UINT, const WPARAM, const LPARAM);
			
		public:
			void Print();
		};
	}
}

#endif