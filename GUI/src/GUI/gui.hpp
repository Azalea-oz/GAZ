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

#ifdef AZ_DEBUG
#if AZ_DEBUG > 1
#warning "in gui, AZ_DEBUG higher than 1."
#endif
#include"../../DEBUG/AzDebug.hpp"
#endif

#include"../defines.hpp"
#include"../WCLASS/wclass.hpp"
#include"../PAINT/paint.hpp"
#include"../EVENT/event.hpp"
#include"../UTIL/utility.hpp"
#include"../SINGLETON/singleton.hpp"

#define WINDOW_CHILD 0xffff

#define EBREAK (0)
#define ECALL (1)


namespace AZ{
	namespace GUI{
		
		typedef int CODE;
		
		class WINDOW;
		class HANDLEMAP;
		
		using WINDOWPTR =  WINDOW*;
		
		class HANDLEITEMS{
			WINDOW *window;
			HDC hdc;
			HDC hmem;
			HBITMAP hbm;
			
		public:
			HANDLEITEMS();
			HANDLEITEMS(WINDOW*);
			//HANDLEITEMS(const HANDLEITEMS&);
			//HANDLEITEMS(HANDLEITEMS&&);
			~HANDLEITEMS();
			
			void Resize(int, int);
			void Set(WINDOW*);
			WINDOW* GetWINDOW();
			HDC GetHDC();
			HBITMAP GetHBITMAP();
			
			/*
			HANDLEITEMS operator=(const HANDLEITEMS &obj){
				
				window = obj.window;
				hmem = obj.hmem;
				hbm = obj.hbm;
				
				return *this;
			}
			HANDLEITEMS& operator=(HANDLEITEMS &&obj){
				
				window = obj.window;
				hmem = obj.hmem;
				hbm = obj.hbm;
				
				obj.window = nullptr;
				obj.hmem = nullptr;
				obj.hbm = nullptr;
				
				return *this;
			}*/
		};
		
		class HANDLEMAP : public UTIL::Singleton<HANDLEMAP>{
			std::map<HWND, HANDLEITEMS> hWndMap;
		public:
			HANDLEMAP();
			~HANDLEMAP();
			HANDLEITEMS* find(HWND);
			bool Register(HWND, WINDOW*);
			bool Remove(HWND);
		};
		
		// template化したい
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
		
		/*
		class HDCMAP : public UTIL::Singleton<DCMAP>{
			std::map<HWND, std::pair<HDC, HBITMAP> > hDcMap;
		public:
			HDCMAP();
			~HDCMAP();
			HDC* find(HWND);
			bool Register(HWND, std::pair<HDC, HBITMAP>);
			bool Remove(HWND);
			
			void DebugPrint();
		};
		*/
		
		class WREG{
			HWND *hwnd;
			const HWND GetHandle();
		public:
			WREG();
			bool Register();
			
			void SetWndHandle(const HWND*);
			
		private:
			UINT cbSize;
		public:
			void SetSize(const UINT);
			const UINT GetSize();
			
		/////////////////////////////////////
		// Window class
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		private:
			WNDCLASSEXA wcex;
			
		public:
			void SetWcex(WNDCLASSEXA);
			WNDCLASSEXA GetWcex();
		
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		private:
			WNDCLASSEXW wcex;
			
		public:
			void SetWcex(WNDCLASSEXW);
			WNDCLASSEXW GetWcex();
		#endif
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window class style
		private:
			UINT style;
			void SetStyle(const UINT, const HWND);
			void AddStyle(const UINT, const HWND);
			
		public:
			void SetStyle(const UINT);
			void AddStyle(const UINT);
			const UINT GetStyle();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window Proc
		private:
			WNDPROC lpfnWndProc;
			void SetWndProc(WNDPROC, HWND);
			const WNDPROC GetWndProc(HWND);
			
			WNDPROC DefProc;
			
		public:
			void SetWndProc(WNDPROC);
			const WNDPROC GetWndProc();
			
			void SetDefProc(const WNDPROC);
			const WNDPROC GetDefProc();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window extra memories
		private:
			int cbClsExtra;
			int cbWndExtra;
			void SetClsExtra(const int, HWND);
			void SetWndExtra(const int, HWND);
			const int GetClsExtra(HWND);
			const int GetWndExtra(HWND);
			
		public:
			void SetClsExtra(const int);
			void SetWndExtra(const int);
			const int GetClsExtra();
			const int GetWndExtra();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Windnow instance
		private:
			HINSTANCE hInstance;
			void SetInstance(const HINSTANCE, HWND);
			const HINSTANCE GetInstance(HWND);
			
		public:
			void SetInstance(const HINSTANCE);
			const HINSTANCE GetInstance();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window icon
		private:
			HICON hIcon;
			HICON hIconSm;
			void SetIcon(HICON, HWND);
			void SetIconSm(HICON, HWND);
			const HICON GetIcon(HWND);
			const HICON GetIconSm(HWND);
			
		public:
			void SetIcon(HICON);
			void SetIconSm(HICON);
			const HICON GetIcon();
			const HICON GetIconSm();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window cursor
		private:
			HCURSOR hCursor;
			void SetCursor(HCURSOR, HWND);
			const HCURSOR GetCursor(HWND);
			
		public:
			void SetCursor(HCURSOR);
			const HCURSOR GetCursor();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window Background color
		private:
			HBRUSH hbrBackground;
			void SetBKGColor(const HBRUSH, HWND);
			const HBRUSH GetBKGColor(HWND);
			
		public:
			void SetBKGColor(const HBRUSH);
			const HBRUSH GetBKGColor();
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window menu name
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		private:
			std::string lpszMenuName;
			void SetMenuName(const std::string, HWND);
			const std::string GetMenuName(HWND);
		public:
			void SetMenuName(const std::string);
			const std::string GetMenuName();
			
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		private:
			std::wstring lpszMenuName;
			void SetMenuName(const std::wstring, HWND);
			const std::wstring GetMenuName(HWND);
			
		public:
			void SetMenuName(const std::wstring);
			const std::wstring GetMenuName();
		#endif
		/////////////////////////////////////
			
		/////////////////////////////////////
		// Window class name
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		private:
			std::string lpszClassName;
			void SetClassName(const std::string, HWND);
			const std::string GetClassName(HWND);
		public:
			void SetClassName(const std::string);
			const std::string GetClassName();
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		private:
			std::wstring lpszClassName;
			void SetClassName(const std::wstring, HWND);
			const std::wstring GetClassName(HWND);
		#endif
			
		public:
			void SetClassName(const std::wstring);
			const std::wstring GetClassName();
		/////////////////////////////////////
		};
		
		class WINDOW : public STATE{
			
			WREG *wreg;
			static WINDOW* tmp;
			
			bool Error;
			
			void InitWindowClass();
			void InitFrameRate(int);
			
			//function pointer
			using WPROC = LRESULT (WINDOW::*)(HWND, UINT, WPARAM, LPARAM);
			WPROC Proc;
			using ENTRYPROC = LRESULT CALLBACK (*)(HWND, UINT, WPARAM, LPARAM);
			
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			static LRESULT CALLBACK EntryProc(HWND, UINT, WPARAM, LPARAM);
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			static LRESULT CALLBACK EntryProc(HWND, UINT, WPARAM, LPARAM);
		#endif
			
		public:
			static ENTRYPROC GetEntry();
			
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
			
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			std::string GetClassName();
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			std::wstring GetClassName();
		#endif
			
			//register window
			WINDOW& Register();
			
		private:
			void _Register();
			
		public:
			
			LRESULT MyProc(HWND, UINT, WPARAM, LPARAM);
			class MODE{
				WINDOW *wp;
				bool state;
			public:
				MODE(WINDOW*);
				MODE(WINDOW*, bool);
				~MODE();
				
				void Enable(bool);
				bool is();
			} Unicode, DBuff, DBuffDIB, DClick, AutoReSize, GPUAPI, Borderless;
			
			struct EVFLAG{
				bool sizing;
				
				EVFLAG();
			} EvFlag;
		protected:
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			const WNDCLASSEX GetWcex();
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			const WNDCLASSEXW GetWcex();
			#endif
			
		// TITLE
		protected:
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			std::string _Title;
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			std::wstring _Title;
			#endif
			
		public:
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			WINDOW& SetTitle(const std::string);
			std::string GetTitle();
			bool ChangeTitle(const std::string);
			
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			WINDOW& SetTitle(const std::wstring);
			std::wstring GetTitle();
			bool ChangeTitle(const std::wstring);
			#endif
			
			
			
			
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
			
			// set window class style
			WINDOW& setREDRAW(bool, bool);
			WINDOW& setDBLCLKS(bool);
			WINDOW& setDC(bool, bool, bool);
			WINDOW& setGLOBAL(bool);
			
			// set window style
			WINDOW& setBORDER(bool);
			WINDOW& setCAPTION(bool);
			WINDOW& setCHILD(bool);
			WINDOW& setCLIPCHILDREN(bool);
			WINDOW& setCLIPSIBLINGS(bool);
			WINDOW& setDISABLED(bool);
			WINDOW& setDLGFRAME(bool);
			WINDOW& setGROUP(bool);
			WINDOW& setSCROLL(bool, bool);
			WINDOW& setCAPTIONBOX(bool, bool, bool);
			WINDOW& setMIN(bool);
			WINDOW& setMAX(bool);
			WINDOW& setTABSTOP(bool);
			WINDOW& setPOPUP(bool);
			WINDOW& setVISIBLE(bool);
			WINDOW& setTITLEDWINDOW(bool);
			
			// set extended window style
			WINDOW& setABSPOTION(bool);
			WINDOW& setACCEPTFILES(bool);
			WINDOW& setCLIENTEDGE(bool);
			WINDOW& setCONTEXTHELP(bool);
			WINDOW& setLEFTSCROLLBAR(bool);
			WINDOW& setMDICHILD(bool);
			WINDOW& setNOPARENTNOTIFY(bool);
			WINDOW& setTOOLWINDOW(bool);
			WINDOW& setTOPMOST(bool);
			WINDOW& setTRANSPARENT(bool);
			
			
			DWORD GetExStyle();
			DWORD GetWindowStyle();
			
		protected:
			HWND hwnd;
			HWND hparent;
			MSG msg;
			HINSTANCE hinst;
			HMENU Menu;
			
			std::vector<std::pair<HMENU, WINDOW*> > ChildWindow;
		public:
			
			WINDOW();
			WINDOW(const int, const int);
			
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			WINDOW(const int, const int, const std::string);
			WINDOW(const int, const int, const std::string, const std::string);
			WINDOW(const std::string);
			WINDOW(const std::string, const std::string);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			WINDOW(const int, const int, const std::wstring);
			WINDOW(const int, const int, const std::wstring, const std::wstring);
			WINDOW(const std::wstring);
			WINDOW(const std::wstring, const std::wstring);
			#endif
			
			virtual ~WINDOW();
			
			WINDOW& WindowSize(const int, const int);
			WINDOW& WindowPos(const int, const int);
			
			
			HINSTANCE GetInst();
			
			void ResizeClient();
			void ReSizeWindow(const int, const int);
			
			bool Create();
			bool Create(const std::string);
			bool Create(const std::wstring);
			
			void Child(WINDOW&, const HMENU);
			void Child(bool);
			bool isChild();
			
			void SetMenuId(const HMENU);
			
			bool isSysProc(UINT);
			LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);
			LRESULT SysProc(HWND, UINT, WPARAM, LPARAM);
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
			WINDOW& GetTopParent();
		protected:
			void SetHandle(const HWND);
			void SetParentHandle(const HWND);
			
			
		private:
			static MOUSE _mouse;
			
		private:
			bool RegisterFlag;
			
			//LRESULT CALLBACK (*CallProc)(HWND, UINT, WPARAM, LPARAM);
			void InitCodeArray();
		protected:
			
		public:
			CODE Render(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp);
			
		protected:
			
			void ESetProc();
			std::array<CODE (WINDOW::*)(const HWND, const UINT, const WPARAM, const LPARAM), 24> CodeFuncArray;
			
			CODE _ESIZE(const HWND, const UINT, const WPARAM, const LPARAM);
			
			// virtual event function
			virtual CODE ECREATE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ECLOSE(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EDESTROY(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ECOMMAND(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMCOMMAND(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMMOVE(const HWND, const UINT, const WPARAM, const LPARAM);
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
			virtual CODE ENCCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EDCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ENCDCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMDOWN(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ENCMDOWN(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EMUP(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE ENCMUP(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EHOLD(const HWND, const UINT, const WPARAM, const LPARAM);
			virtual CODE EPAINT(const HWND, const UINT, const WPARAM, const LPARAM, HDC);
			virtual CODE EMWHEEL(const HWND, const UINT, const WPARAM, const LPARAM);
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
			CODE _EMCOMMAND(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMMOVE(const HWND, const UINT, const WPARAM, const LPARAM);
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
			CODE _ENCCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EDCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ENCDCLICK(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMDOWN(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ENCMDOWN(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMUP(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _ENCMUP(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EHOLD(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EPAINT(const HWND, const UINT, const WPARAM, const LPARAM);
			CODE _EMWHEEL(const HWND, const UINT, const WPARAM, const LPARAM);
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
		public:
			void Wait();
			void FPSLock(int);
			void UpdateDisplay();
			
		private:
			class FPSTIMER{
				int count;
				int FrameRate;
				double RateTime;
				double fps;
				
				std::chrono::system_clock::time_point a, b;
				std::chrono::system_clock::time_point last;

				std::chrono::duration<double, std::milli> work_time;
				std::chrono::duration<double, std::milli> sleep_time;
			public:
				FPSTIMER();
				void wait();
				void calcfps();
				void countup();
				void Lockfps(int);
			} _fpstimer;
			
			
		//デバッグ
		public:
			void Print();
		};
	}
}