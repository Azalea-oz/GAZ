#include"gui.hpp"

//#define AZ_DEBUG 1
namespace AZ{
	namespace GUI{
		
		HANDLEITEMS::HANDLEITEMS() : hdc(nullptr), window(nullptr), hmem(nullptr), hbm(nullptr){}
		HANDLEITEMS::HANDLEITEMS(WINDOW* wp) : window(wp), hmem(nullptr), hbm(nullptr){
			/*
			if(wp->DBuff.is() == true){
				hdc = GetDC(wp->GetHandle());
				hmem = CreateCompatibleDC(hdc);
				hbm = CreateCompatibleBitmap(hdc, wp->GetSize()[0], wp->GetSize()[1]);
				SelectObject(hmem, hbm);
				SelectObject(hmem, GetStockObject(DC_PEN));
				SelectObject(hmem, GetStockObject(DC_BRUSH));
			} else{
				hmem = nullptr;
				hbm = nullptr;
			}*/
		}
		/*
		HANDLEITEMS::HANDLEITEMS(const HANDLEITEMS &obj){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- COPY --------------");
			#endif
			window = obj.window;
			hmem = obj.hmem;
			hbm = obj.hbm;
		}
		HANDLEITEMS::HANDLEITEMS(HANDLEITEMS &&obj){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- MOVE --------------");
			#endif
			window = obj.window;
			hmem = obj.hmem;
			hbm = obj.hbm;
			
			obj.window = nullptr;
			obj.hmem = nullptr;
			obj.hbm = nullptr;
		}
		*/
		
		HANDLEITEMS::~HANDLEITEMS(){
			if(hmem != nullptr) DeleteDC(hmem);
			if(hbm != nullptr)  DeleteObject(hbm);
		}
		void HANDLEITEMS::Resize(int w, int h){
			if(hmem != nullptr) DeleteDC(hmem);
			if(hbm != nullptr) DeleteObject(hbm);
			Set(window);
		}
		void HANDLEITEMS::Set(WINDOW *wp){
			window = wp;
			if(wp->DBuff.is() == true){
				hdc = GetDC(wp->GetHandle());
				hmem = CreateCompatibleDC(hdc);
				hbm = CreateCompatibleBitmap(hdc, wp->GetSize()[0], wp->GetSize()[1]);
				SelectObject(hmem, hbm);
				SelectObject(hmem, GetStockObject(DC_PEN));
				SelectObject(hmem, GetStockObject(DC_BRUSH));
				if(hdc) ReleaseDC(window->GetHandle(), hdc);
			} else{
				hmem = nullptr;
				hbm = nullptr;
			}
		}
		WINDOW* HANDLEITEMS::GetWINDOW(){
			return window;
		}
		HDC HANDLEITEMS::GetHDC(){
			return hmem;
		}
		HBITMAP HANDLEITEMS::GetHBITMAP(){
			return hbm;
		}
		
		HANDLEMAP::HANDLEMAP(){}
		HANDLEMAP::~HANDLEMAP(){}
		
		HANDLEITEMS* HANDLEMAP::find(HWND hwnd){
			std::map<HWND, HANDLEITEMS>::iterator itr = hWndMap.find(hwnd);
			if(itr != hWndMap.end()) return &(itr->second);
			return nullptr;
		}
		
		bool HANDLEMAP::Register(HWND hwnd, WINDOW *wp){
			HANDLEITEMS item(wp);
			
			bool tmp = hWndMap.insert(std::make_pair(hwnd, item)).second;
			if(tmp){
				std::map<HWND, HANDLEITEMS>::iterator itr = hWndMap.find(hwnd);
				itr->second.Set(wp);
			}
			return  tmp;
		}
		
		bool HANDLEMAP::Remove(HWND hwnd){
			std::map<HWND, HANDLEITEMS>::iterator itr = hWndMap.find(hwnd);
			if(itr != hWndMap.end()){
				hWndMap.erase(itr);
				return true;
			}
			return false;
		}
		
		PROCMAP::PROCMAP(){}
		PROCMAP::~PROCMAP(){}
		
		WINDOW* PROCMAP::find(HWND hwnd){
			std::map<HWND, WINDOW*>::iterator itr = hWndMap.find(hwnd);
			if(itr != hWndMap.end()) return itr->second;
			return nullptr;
		}
		
		bool PROCMAP::Register(HWND hwnd, WINDOW *item){
			return  hWndMap.insert(std::make_pair(hwnd, item)).second;
		}
		
		bool PROCMAP::Remove(HWND hwnd){
			std::map<HWND, WINDOW*>::iterator itr = hWndMap.find(hwnd);
			if(itr != hWndMap.end()){
				hWndMap.erase(itr);
				return true;
			}
			return false;
		}
		
		
		void PROCMAP::DebugPrint(){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- PROCMAP --------------");
			DEBUG::DebugConsole::Get_Instance().Log((int)hWndMap.size());
			for(auto itr : hWndMap){
				DEBUG::DebugConsole::Get_Instance().Log((LPVOID)itr.first);
				DEBUG::DebugConsole::Get_Instance().Log((LPVOID)itr.second);
			}
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log("");
			#endif
		}
		
		WINDOW::MODE::MODE(WINDOW *w){
			wp = w;
			state = false;
		}
		WINDOW::MODE::MODE(WINDOW *w, bool f){
			wp = w;
			state = f;
		}
		WINDOW::MODE::~MODE(){}
		void WINDOW::MODE::Enable(const bool flag){
			state = flag;
		}
		
		bool WINDOW::MODE::is(){
			return state;
		}
		
		void WINDOW::InitWindowClass(){
			cbSize = Unicode.is()? sizeof(WNDCLASSEXW) : sizeof(WNDCLASSEX);
			style = CS_HREDRAW | CS_VREDRAW;
			cbClsExtra = 0;
			cbWndExtra = 0;
			hInstance = GetModuleHandle(NULL);
			hIcon = LoadIcon(NULL , IDI_APPLICATION);
			hIconSm = LoadIcon(NULL , IDI_APPLICATION);
			hCursor = LoadCursor(NULL, IDC_ARROW);
			hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
			lpszMenuName = "AzMenu";
			lpszClassName = "AzWindow";
			lpszMenuNameW = L"AzMenu";
			lpszClassNameW = L"AzWindow";
			
			lpfnWndProc = Unicode.is()? EntryProcW : EntryProcA;
			DefProc = Unicode.is()? DefWindowProcW : DefWindowProcA;
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			
			//InitFrameRate(30);
		}
		
		using CODE = int;
		WINDOW* WINDOW::tmp = nullptr;
		WINDOW::WINDOW() :
			STATE(), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Border(false), Proc(&WINDOW::WindowProc){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = "Azalea Window";
				_TitleW = L"Azalea Window";
		}
		WINDOW::WINDOW(const int w, const int h) : 
			STATE(w, h), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Border(false), Proc(&WINDOW::WindowProc){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = "Azalea Window";
				_TitleW = L"Azalea Window";
		}
		
		WINDOW::WINDOW(const int w, const int h, const std::string title) : 
			STATE(w, h), Unicode(this), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Border(false), Proc(&WINDOW::WindowProc){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = title;
				_TitleW = L"Azalea Window";
		}
		WINDOW::WINDOW(const int w, const int h, const std::wstring title) : 
			STATE(w, h), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Border(false), Proc(&WINDOW::WindowProc){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = "Azalea Window";
				_TitleW = title;
		}
		WINDOW::WINDOW(const std::string title) : 
			STATE(), Unicode(this), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Border(false), Proc(&WINDOW::WindowProc){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = title;
				_TitleW = L"Azalea Window";
		}
		WINDOW::WINDOW(const std::wstring title) : 
			STATE(), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Border(false), Proc(&WINDOW::WindowProc){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = "Azalea Window";
				_TitleW = title;
		}
		WINDOW::~WINDOW(){
			#ifdef AZ_DEBUG
			if(&(DEBUG::DebugConsole::Get_Instance()) != nullptr) delete &(DEBUG::DebugConsole::Get_Instance());
			#endif
		}
		
		WINDOW& WINDOW::WClassSize(const UINT Size){				cbSize = Size;				return *this;}
		WINDOW& WINDOW::WClassStyle(const UINT Style){				style = Style;				return *this;}
		WINDOW& WINDOW::WClassWndProc(WNDPROC lpProc){				lpfnWndProc = lpProc;		return *this;}
		WINDOW& WINDOW::WClassClsExtra(const int CE){				cbClsExtra = CE;			return *this;}
		WINDOW& WINDOW::WClassWndExtra(const int WE){				cbWndExtra = WE;			return *this;}
		WINDOW& WINDOW::WClassInstance(const HINSTANCE hInst){		hInstance = hInst;			return *this;}
		WINDOW& WINDOW::WClassIcon(HICON Icon){						hIcon = Icon;				return *this;}
		WINDOW& WINDOW::WClassIconSm(HICON IconSm){					hIconSm = IconSm;			return *this;}
		WINDOW& WINDOW::WClassCursor(HCURSOR Cursor){				hCursor = Cursor;			return *this;}
		WINDOW& WINDOW::WClassBackground(const HBRUSH BG){			hbrBackground = BG;			return *this;}
		WINDOW& WINDOW::WClassMenuName(const std::string MenuName){	lpszMenuName = MenuName;	return *this;}
		WINDOW& WINDOW::WClassMenuName(const std::wstring MenuName){	lpszMenuNameW = MenuName;	return *this;}
		WINDOW& WINDOW::WClassName(const std::string ClassName){	lpszClassName = ClassName;	return *this;}
		WINDOW& WINDOW::WClassName(const std::wstring ClassName){	lpszClassNameW = ClassName;	return *this;}
		
		std::string WINDOW::GetClassNameA(){return lpszClassName;}
		std::wstring WINDOW::GetClassNameW(){return lpszClassNameW;}
		
		HINSTANCE WINDOW::GetInst(){
			return hInstance;
		}
		
		WINDOW& WINDOW::Register(){
			RegisterFlag = true;
			return *this;
		}
		void WINDOW::_Register(){
			if(RegisterFlag == true){
				if(Unicode.is()){
					wcexw.cbSize = cbSize;
					wcexw.style = style;
					wcexw.lpfnWndProc = lpfnWndProc;
					wcexw.cbClsExtra = cbClsExtra;
					wcexw.cbWndExtra = cbWndExtra;
					wcexw.hInstance = hInstance;
					wcexw.hIcon = hIcon;
					wcexw.hIconSm = hIconSm;
					wcexw.hCursor = hCursor;
					wcexw.hbrBackground = hbrBackground;
					wcexw.lpszMenuName = lpszMenuNameW.c_str();
					wcexw.lpszClassName = lpszClassNameW.c_str();
					if(!RegisterClassExW(&wcexw)){
						#ifdef AZ_DEBUG
						DEBUG::error_dialog(NULL, GetTitleW().c_str());
						#endif
					}
				} else{
					wcex.cbSize = cbSize;
					wcex.style = style;
					wcex.lpfnWndProc = lpfnWndProc;
					wcex.cbClsExtra = cbClsExtra;
					wcex.cbWndExtra = cbWndExtra;
					wcex.hInstance = hInstance;
					wcex.hIcon = hIcon;
					wcex.hIconSm = hIconSm;
					wcex.hCursor = hCursor;
					wcex.hbrBackground = hbrBackground;
					wcex.lpszMenuName = lpszMenuName.c_str();
					wcex.lpszClassName = lpszClassName.c_str();
					
					if(!RegisterClassEx(&wcex)){
						#ifdef AZ_DEBUG
						DEBUG::error_dialog(NULL, GetTitleW().c_str());
						#endif
					}
				}
			}
			
		}
		const WNDCLASSEX WINDOW::GetWcex(){return wcex;}
		//const WNDCLASSEX WINDOW::GetWcexW(){return wcexw;}
		
		LRESULT CALLBACK WINDOW::EntryProcA(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			//WINDOW *ptr = PROCMAP::Get_Instance().find(hwnd);
			WINDOW *ptr;
			if(HANDLEMAP::Get_Instance().find(hwnd) == nullptr) ptr = nullptr;
			else ptr = HANDLEMAP::Get_Instance().find(hwnd)->GetWINDOW();
			
			//hash map(window handle, window proc) 
			if(ptr != nullptr){
				if(msg == WM_DESTROY){
					//PROCMAP::Get_Instance().Remove(hwnd);
					HANDLEMAP::Get_Instance().Remove(hwnd);
				}
				return ptr->MyProc(hwnd, msg, wp, lp);
			} else{
				if(msg == WM_CREATE || msg == WM_INITDIALOG){
					ptr = (WINDOW*)(((LPCREATESTRUCT)lp)->lpCreateParams);
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)(ptr));
					ptr->SetHandle(hwnd);
					ptr->_EVENT(hwnd, msg, wp, lp, &_ECREATE, &ECREATE);
					//ptr->ECREATE(hwnd, msg, wp, lp);
				}
			}
			//return 0L;
			return DefWindowProc(hwnd, msg, wp, lp);
		}
		LRESULT CALLBACK WINDOW::EntryProcW(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			//WINDOW *ptr = PROCMAP::Get_Instance().find(hwnd);
			WINDOW *ptr;
			if(HANDLEMAP::Get_Instance().find(hwnd) == nullptr) ptr = nullptr;
			else ptr = HANDLEMAP::Get_Instance().find(hwnd)->GetWINDOW();
			
			//hash map(window handle, window proc)
			if(ptr != nullptr){
				if(msg == WM_DESTROY){
					//PROCMAP::Get_Instance().Remove(hwnd);
					HANDLEMAP::Get_Instance().Remove(hwnd);
				}
				return ptr->MyProc(ptr->GetHandle(), msg, wp, lp);
			} else{
				if(msg == WM_CREATE || msg == WM_INITDIALOG){
					ptr = (WINDOW*)(((LPCREATESTRUCT)lp)->lpCreateParams);
					SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)(ptr));
					ptr->SetHandle(hwnd);
					ptr->_EVENT(hwnd, msg, wp, lp, &_ECREATE, &ECREATE);
					//ptr->ECREATE(hwnd, msg, wp, lp);
				}
			}
			//return 0L;
			return DefWindowProcW(hwnd, msg, wp, lp);
		}
		
		LRESULT WINDOW::MyProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			#ifdef AZ_DEBUG
			if(Unicode.is()){
				std::wstring _str = L"[";
				_str += GetTitleW();
				_str += L"] > ";
				_str += CvtMsgCodetowc(msg);
				//DEBUG::DebugConsole::Get_Instance().Log(_str);
			} else{
				std::string _str = "[";
				_str += GetTitleA();
				_str += "] > ";
				//_str += CvtMsgCodetoc(msg);
				//DEBUG::DebugConsole::Get_Instance().Log(_str);
			}
			#endif
			return (this->WindowProc)(hwnd, msg, wp, lp);
		}
		
		WINDOW& WINDOW::SetExStyle(const DWORD es){
			_ExStyle = es;
			return *this;
		}
		WINDOW& WINDOW::SetWindowStyle(const DWORD s){
			_WindowStyle = s;
			return *this;
		}
		DWORD WINDOW::GetWindowStyle(){
			return _WindowStyle;
		}
		DWORD WINDOW::GetExStyle(){
			return _ExStyle;
		}
		WINDOW& WINDOW::setREDRAW(bool v, bool h){
			if(v) style |= CS_VREDRAW;
			else style &= ~CS_VREDRAW;
			if(h) style |= CS_HREDRAW;
			else style &= ~CS_HREDRAW;
			return *this;
		}
		WINDOW& WINDOW::setDBLCLKS(bool f){
			if(f) style |= CS_DBLCLKS;
			else style &= ~CS_DBLCLKS;
			return *this;
		}
		WINDOW& WINDOW::setDC(bool cl, bool own, bool parent){
			if(cl) style |= CS_CLASSDC;
			else style &= ~CS_CLASSDC;
			if(own) style |= CS_OWNDC;
			else style &= ~CS_OWNDC;
			if(parent) style |= CS_PARENTDC;
			else style &= ~CS_PARENTDC;
			return *this;
		}
		WINDOW& WINDOW::setGLOBAL(bool f){
			if(f) style |= CS_GLOBALCLASS;
			else style &= ~CS_GLOBALCLASS;
			return *this;
		}
		WINDOW& WINDOW::setBORDER(bool f){
			if(f) _WindowStyle |= WS_BORDER;
			else _WindowStyle &= ~WS_BORDER;
			return *this;
		}
		WINDOW& WINDOW::setCAPTION(bool f){
			if(f) _WindowStyle |= WS_CAPTION;
			else _WindowStyle &= ~WS_CAPTION;
			return *this;
		}
		WINDOW& WINDOW::setCHILD(bool f){
			if(f) _WindowStyle |= WS_CHILD;
			else _WindowStyle &= ~WS_CHILD;
			return *this;
		}
		WINDOW& WINDOW::setCLIPCHILDREN(bool f){
			if(f) _WindowStyle |= WS_CLIPCHILDREN;
			else _WindowStyle &= ~WS_CLIPCHILDREN;
			return *this;
		}
		WINDOW& WINDOW::setCLIPSIBLINGS(bool f){
			if(f) _WindowStyle |= WS_CLIPSIBLINGS;
			else _WindowStyle &= ~WS_CLIPSIBLINGS;
			return *this;
		}
		WINDOW& WINDOW::setDISABLED(bool f){
			if(f) _WindowStyle |= WS_DISABLED;
			else _WindowStyle &= ~WS_DISABLED;
			return *this;
		}
		WINDOW& WINDOW::setDLGFRAME(bool f){
			if(f) _WindowStyle |= WS_DLGFRAME;
			else _WindowStyle &= ~WS_DLGFRAME;
			return *this;
		}
		WINDOW& WINDOW::setGROUP(bool f){
			if(f) _WindowStyle |= WS_GROUP;
			else _WindowStyle &= ~WS_GROUP;
			return *this;
		}
		WINDOW& WINDOW::setSCROLL(bool h, bool v){
			if(h) _WindowStyle |= WS_HSCROLL;
			else _WindowStyle &= ~WS_HSCROLL;
			if(v) _WindowStyle |= WS_VSCROLL;
			else _WindowStyle &= ~WS_VSCROLL;
			return *this;
		}
		WINDOW& WINDOW::setCAPTIONBOX(bool min, bool max, bool close){
			if(min) _WindowStyle |= WS_MINIMIZEBOX;
			else _WindowStyle &= ~WS_MINIMIZEBOX;
			if(max) _WindowStyle |= WS_MAXIMIZEBOX;
			else _WindowStyle &= ~WS_MAXIMIZEBOX;
			if(!close) style |= CS_NOCLOSE;
			else style &= ~CS_NOCLOSE;
			return *this;
		}
		WINDOW& WINDOW::setMIN(bool f){
			if(f) _WindowStyle |= WS_MINIMIZE;
			else _WindowStyle &= ~WS_MINIMIZE;
			return *this;
		}
		WINDOW& WINDOW::setMAX(bool f){
			if(f) _WindowStyle |= WS_MAXIMIZE;
			else _WindowStyle &= ~WS_MAXIMIZE;
			return *this;
		}
		WINDOW& WINDOW::setTABSTOP(bool f){
			if(f) _WindowStyle |= WS_TABSTOP;
			else _WindowStyle &= ~WS_TABSTOP;
			return *this;
		}
		WINDOW& WINDOW::setPOPUP(bool f){
			if(f) _WindowStyle |= WS_POPUP;
			else _WindowStyle &= ~WS_POPUP;
			return *this;
		}
		WINDOW& WINDOW::setVISIBLE(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setTITLEDWINDOW(bool f){
			if(f) _WindowStyle |= WS_OVERLAPPEDWINDOW;
			else _WindowStyle &= ~WS_OVERLAPPEDWINDOW;
			return *this;
		}
		WINDOW& WINDOW::setABSPOTION(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setACCEPTFILES(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setCLIENTEDGE(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setCONTEXTHELP(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setLEFTSCROLLBAR(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setMDICHILD(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setNOPARENTNOTIFY(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setTOOLWINDOW(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setTOPMOST(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		WINDOW& WINDOW::setTRANSPARENT(bool f){
			if(f) _WindowStyle |= WS_VISIBLE;
			else _WindowStyle &= ~WS_VISIBLE;
			return *this;
		}
		
		WINDOW& WINDOW::SetTitle(const std::string title){
			_Title = title;
			return *this;
		}
		WINDOW& WINDOW::SetTitle(const std::wstring title){
			_TitleW = title;
			return *this;
		}
		WINDOW& WINDOW::WindowSize(const int w, const int h){
			SetSize(w, h);
			return *this;
		}
		WINDOW& WINDOW::WindowPos(const int x, const int y){
			SetPos(x, y);
			return *this;
		}
		std::wstring WINDOW::GetTitleW(){
			return _TitleW;
		}
		std::string WINDOW::GetTitleA(){
			return _Title;
		}
		
		bool WINDOW::ChangeTitle(const std::string title){
			_Title = title;
			return SetWindowTextA(GetHandle(), title.c_str());
		}
		bool WINDOW::ChangeTitle(const std::wstring title){
			_TitleW = title;
			return SetWindowTextW(GetHandle(), title.c_str());
		}
		
		/*
		WINDOW& SetMenu(const std::string menu){
			_Menu = menu;
		}
		WINDOW& SetMenu(const std::wstring menu){
			_MenuW = menu;
		}
		
		std::string GetMenuA(){
			return _Menu;
		}
		std::wstring GetMenuW(){
			return _MenuW;
		}
		
		bool ChangeMenu(const std::string){
			return SetMenu
		}
		bool ChangeMenu(const std::wstring){
			
		}
		*/
		
		WINDOW& WINDOW::Borderless(){
			Border = true;
			return *this;
		}
		void WINDOW::ResizeClient(){
			RECT wrect, crect;
			
			if(Border && (GetParentHandle() == nullptr)){
				GetWindowRect(hwnd, &wrect);
				SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_BORDER);
				POINT pt;
				int tmpx = GetSystemMetrics(SM_CXFRAME) - GetSystemMetrics(SM_CXBORDER);
				int tmpy = GetSystemMetrics(SM_CYFRAME) - GetSystemMetrics(SM_CYBORDER);
				pt.x = wrect.left + tmpx;
				pt.y = wrect.top + tmpy;
				ScreenToClient(hwnd, &pt);
				SetWindowPos(
					hwnd, nullptr, pt.x, pt.y,
					(wrect.right - wrect.left) - tmpx * 2,
					(wrect.bottom - wrect.top) - tmpy * 2,
					SWP_DRAWFRAME | SWP_NOZORDER | SWP_NOMOVE);
			}
			GetWindowRect(hwnd, &wrect);
			GetClientRect(hwnd, &crect);
			
			int _Width = (wrect.right - wrect.left) - (crect.right - crect.left) + GetSize()[0];
			int _Height = (wrect.bottom - wrect.top) - (crect.bottom - crect.top) + GetSize()[1];
			
			SetWindowPos(hwnd, HWND_TOP, 0, 0, _Width, _Height, SWP_NOOWNERZORDER|SWP_NOMOVE);
			//SetWindowPos(hwnd, NULL, 0, 0, _Width, _Height, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE);
		}
		
		void WINDOW::ReSizeWindow(const int w, const int h){
			SetSize(w, h);
			SetWindowPos(GetHandle(), 0, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
		}
		
		void WINDOW::Create(){
			_Register();
			
			if(Unicode.is()){
				hwnd = CreateWindowExW(
					_ExStyle,
					lpszClassNameW.c_str(), _TitleW.c_str(),
					_WindowStyle,
					GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
					GetParentHandle(), Menu, hInstance, this);
			} else{
				hwnd = CreateWindowExA(
					_ExStyle,
					lpszClassName.c_str(), _Title.c_str(),
					_WindowStyle,
					GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
					GetParentHandle(), Menu, hInstance, this);
			}
			if(hwnd == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL, GetTitleW().c_str());
				#endif
			}
			
			//PROCMAP::Get_Instance().Register(GetHandle(), this);
			HANDLEMAP::Get_Instance().Register(GetHandle(), this);
			
			ResizeClient();
			if(GetParentHandle() == nullptr) ESetProc();
			if(ChildWindow.size() != 0){
				for(auto v : ChildWindow){
					v.second->SetParentHandle(GetHandle());
					v.second->SetParent(this);
					v.second->Create();
					v.second->ESetProc();
				}
			}
		}
		void WINDOW::Create(const std::string title){
			_Register();
			
			_Title = title;
			hwnd = CreateWindowExA(
				_ExStyle,
				lpszClassName.c_str(), _Title.c_str(),
				_WindowStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				GetParentHandle(), NULL, hInstance, this);
			if(hwnd == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL, GetTitleW().c_str());
				#endif
			}
			//PROCMAP::Get_Instance().Register(GetHandle(), this);
			HANDLEMAP::Get_Instance().Register(GetHandle(), this);
			
			ResizeClient();
			if(GetParentHandle() == nullptr) ESetProc();
			if(ChildWindow.size() != 0){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("Create Child");
				#endif
				for(auto v : ChildWindow){
					v.second->SetParentHandle(GetHandle());
					v.second->SetParent(this);
					v.second->Create();
					v.second->ESetProc();
					
				}
			}
		}
		void WINDOW::Create(const std::wstring title){
			_Register();
			
			_TitleW = title;
			hwnd = CreateWindowExW(
				_ExStyle,
				lpszClassNameW.c_str(), _TitleW.c_str(),
				_WindowStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				GetParentHandle(), NULL, hInstance, this);
			if(hwnd == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL, GetTitleW().c_str());
				#endif
			}
			//PROCMAP::Get_Instance().Register(GetHandle(), this);
			HANDLEMAP::Get_Instance().Register(GetHandle(), this);
			
			if(GetParentHandle() == nullptr) ResizeClient();
			if(GetParentHandle() == nullptr) ESetProc();
			if(ChildWindow.size() != 0){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("Create Child");
				#endif
				for(auto v : ChildWindow){
					v.second->SetParentHandle(hwnd);
					v.second->SetParent(this);
					v.second->Create();
					v.second->ESetProc();
					
				}
			}
		}
		void WINDOW::Child(WINDOW& ch, const HMENU Id){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("Set Child");
			#endif
			//ch.SetWindowStyle(ch.GetWindowStyle() | WS_CHILD);
			ch.SetMenuId(Id);
			ChildWindow.push_back(std::make_pair(Id,&ch));
		}
		void WINDOW::Child(bool f){
			f ? _WindowStyle | WS_CHILD : _WindowStyle & ~WS_CHILD;
		}
		bool WINDOW::isChild(){
			return _WindowStyle && WS_CHILD;
		}
		void WINDOW::SetMenuId(const HMENU Id){
			Menu = Id;
		}
		
		void WINDOW::SetHandle(const HWND handle){
			hwnd = handle;
		}
		
		HWND WINDOW::GetHandle(){
			return hwnd;
		}
		
		void WINDOW::SetParentHandle(const HWND handle){
			hparent = handle;
		}
		
		HWND WINDOW::GetParentHandle(){
			return hparent;
		}
		
		void WINDOW::SetParent(WINDOW* _Parent){
			Parent = _Parent;
		}
		WINDOW& WINDOW::GetParent(){
			return *Parent;
		}
		
		
		LRESULT WINDOW::WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			PAINTSTRUCT ps;
			HDC hdc;
			CODE code;
			HIMC himc;
			
			switch(msg){
				
			//Custommed user msg
			case WM_COMMAND:
				switch(LOWORD(wp)){
				case AZ_RELATIVE_SIZE:
					if(_ERELATIVESIZE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				}
				if(_EVENT(hwnd, msg, wp, lp, &_CHILDMSG, &CHILDMSG)) return EBack(hwnd, msg, wp, lp);
				if(_EVENT(hwnd, msg, wp, lp, &_ECOMMAND, &ECOMMAND)) return EBack(hwnd, msg, wp, lp);
				return 0;
			
			//CREATE
			case WM_CREATE:
				#if AZ_DEBUG > 0
				DEBUG::DebugConsole::Get_Instance().Log("Proc Called Create");
				#endif
				return _EVENT(hwnd, msg, wp, lp, &_ECREATE, &ECREATE)? EBack(hwnd, msg, wp, lp) : 0;
			
			
			//MOUSE (throw down)
			case WM_LBUTTONDBLCLK:
			case WM_MBUTTONDBLCLK:
			case WM_RBUTTONDBLCLK:
			
			case WM_NCLBUTTONDBLCLK:
			case WM_NCMBUTTONDBLCLK:
			case WM_NCRBUTTONDBLCLK:
				return _EVENT(hwnd, msg, wp, lp, &_EDCLICK, &EDCLICK)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			
			case WM_NCLBUTTONDOWN:
			case WM_NCMBUTTONDOWN:
			case WM_NCRBUTTONDOWN:
				SetTimer(GetHandle(), msg, GetDoubleClickTime(), NULL);
				_mouse.wp = wp;
				_mouse.lp = lp;
				return _EVENT(hwnd, msg, wp, lp, &_EMDOWN, &EMDOWN)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
			
			case WM_NCLBUTTONUP:
			case WM_NCMBUTTONUP:
			case WM_NCRBUTTONUP:
				return _EVENT(hwnd, msg, wp, lp, &_EMUP, &EMUP)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_MOUSEMOVE:
				return _EVENT(hwnd, msg, wp, lp, &_EMOUSE, &EMOUSE)? EBack(hwnd, msg, wp, lp) : 0;
			
			//MDI (throw down)
			case WM_MDIACTIVATE:
			case WM_MDICASCADE:
			case WM_MDICREATE:
			case WM_MDIDESTROY:
			case WM_MDIGETACTIVE:
			case WM_MDIICONARRANGE:
			case WM_MDIMAXIMIZE:
			case WM_MDINEXT:
			case WM_MDIRESTORE:
			case WM_MDITILE:
				return _EVENT(hwnd, msg, wp, lp, &_EMDI, &EMDI)? EBack(hwnd, msg, wp, lp) : 0;
				
			//NC (throw down)
			case WM_NCDESTROY:
				return _EVENT(hwnd, msg, wp, lp, &_ENCDESTROY, &ENCDESTROY)? EBack(hwnd, msg, wp, lp) : 0;
				
			//NC HITTEST
			case WM_NCHITTEST:
				return _EVENT(hwnd, msg, wp, lp, &_ENCHITTEST, &ENCHITTEST)? EBack(hwnd, msg, wp, lp) : 0;
			
			//NC MOUSE (throw down)
			case WM_NCMOUSEMOVE:
				return _EVENT(hwnd, msg, wp, lp, &_ENCMOUSE, &ENCMOUSE)? EBack(hwnd, msg, wp, lp) : 0;
			
			
			//DROP
			case WM_DROPFILES:
				return _EVENT(hwnd, msg, wp, lp, &_EFILE, &EFILE)? EBack(hwnd, msg, wp, lp) : 0;
			
			//EDIT BOX or COMBO BOX (throw down)
			case WM_CLEAR:
			case WM_COPY:
			case WM_CUT:
			case WM_PASTE:
				return _EVENT(hwnd, msg, wp, lp, &_EEDIT, &EEDIT)? EBack(hwnd, msg, wp, lp) : 0;
			
			//CHAR CODE (throw down)
			case WM_CHAR:
			case WM_DEADCHAR:
			case WM_SYSCHAR:
			case WM_SYSDEADCHAR:
				return _EVENT(hwnd, msg, wp, lp, &_ECHAR, &ECHAR)? EBack(hwnd, msg, wp, lp) : 0;
			
			//KEY (throw down)
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				return _EVENT(hwnd, msg, wp, lp, &_EKEY, &EKEY)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_CLOSE:
				return _EVENT(hwnd, msg, wp, lp, &_ECLOSE, &ECLOSE)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_DESTROY:
				return _EVENT(hwnd, msg, wp, lp, &_EDESTROY, &EDESTROY)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_QUIT:
				return _EVENT(hwnd, msg, wp, lp, &_EQUIT, &EQUIT)? EBack(hwnd, msg, wp, lp) : 0;
			
			//SCROLL (throw down)
			case WM_HSCROLL:
			case WM_VSCROLL:
				return _EVENT(hwnd, msg, wp, lp, &_ESCROLL, &ESCROLL)? EBack(hwnd, msg, wp, lp) : 0;
				
			//STATE (throw down)
			case WM_ENABLE:
			case WM_SHOWWINDOW:
				return _EVENT(hwnd, msg, wp, lp, &_ESTATE, &ESTATE)? EBack(hwnd, msg, wp, lp) : 0;
				
			//FOCUS (throw down)
			case WM_KILLFOCUS:
			case WM_SETFOCUS:
				return _EVENT(hwnd, msg, wp, lp, &_EFOCUS, &EFOCUS)? EBack(hwnd, msg, wp, lp) : 0;
				
			//MOVE
			case WM_MOVE:
				return _EVENT(hwnd, msg, wp, lp, &_EMOVE, &EMOVE)? EBack(hwnd, msg, wp, lp) : 0;
				
			//SIZE
			case WM_SIZE:
				return _EVENT(hwnd, msg, wp, lp, &_ESIZE, &ESIZE)? EBack(hwnd, msg, wp, lp) : 0;
			
			//TEXT (throw down)
			case WM_SETTEXT:
			case WM_GETTEXT:
			case WM_GETTEXTLENGTH:
				return _EVENT(hwnd, msg, wp, lp, &_ENCMOUSE, &ENCMOUSE)? EBack(hwnd, msg, wp, lp) : 0;
			
			//MENU (throw down)
			case WM_INITMENU:
			case WM_INITMENUPOPUP:
			case WM_MENUCHAR:
			case WM_MENUSELECT:
				return _EVENT(hwnd, msg, wp, lp, &_EMENU, &EMENU)? EBack(hwnd, msg, wp, lp) : 0;
				
			//ITEM (throw down)
			case WM_MEASUREITEM:
			case WM_DRAWITEM:
				return _EVENT(hwnd, msg, wp, lp, &_EITEM, &EITEM)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_ERASEBKGND:
				if(DBuff.is() == true || DBuffDIB.is() == true){
					HDC hmem = HANDLEMAP::Get_Instance().find(hwnd)->GetHDC();
					Rectangle(hmem, 0, 0, GetSize()[0], GetSize()[1]);
					return 1;
				}
				return _EVENT(hwnd, msg, wp, lp, &_EBKG, &EBKG)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_PAINT:
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(msg);
				#endif
				return _EPAINT(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_IME_SETCONTEXT:
				break;
				
			case WM_NOTIFY:
				
				break;
			case WM_PARENTNOTIFY:
				
				break;
			case WM_SETREDRAW:
				break;
				
			case WM_SYSCOLORCHANGE:
				break;
			case WM_SYSCOMMAND:
				break;
				
			case WM_TIMER:
				return _EVENT(hwnd, msg, wp, lp, &_ETIMER, &ETIMER)? EBack(hwnd, msg, wp, lp) : 0;
			
			default:
				return CustomMsg(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			}
			return EBack(hwnd, msg, wp, lp);
		}
		void WINDOW::InitCodeArray(){
			/*
			CodeFuncArray[static_cast<int>(EVENT_CODE::COMMAND)] = &ECOMMAND;
			CodeFuncArray[static_cast<int>(EVENT_CODE::CREATE)] = &ECREATE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::PAINT)] = &EPAINT;
			CodeFuncArray[static_cast<int>(EVENT_CODE::CLOSE)] = &ECLOSE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::DESTROY)] = &EDESTROY;
			CodeFuncArray[static_cast<int>(EVENT_CODE::MOUSE)] = &EMOUSE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::MDI)] = &EMDI;
			CodeFuncArray[static_cast<int>(EVENT_CODE::NCDESTROY)] = &ENCDESTROY;
			CodeFuncArray[static_cast<int>(EVENT_CODE::NCHITTEST)] = &ENCHITTEST;
			CodeFuncArray[static_cast<int>(EVENT_CODE::NCMOUSE)] = &ENCMOUSE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::EDIT)] = &EEDIT;
			CodeFuncArray[static_cast<int>(EVENT_CODE::CHAR)] = &ECHAR;
			CodeFuncArray[static_cast<int>(EVENT_CODE::KEY)] = &EKEY;
			CodeFuncArray[static_cast<int>(EVENT_CODE::QUIT)] = &EQUIT;
			CodeFuncArray[static_cast<int>(EVENT_CODE::SCROLL)] = &ESCROLL;
			CodeFuncArray[static_cast<int>(EVENT_CODE::ACTIVE)] = &EACTIVE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::FOCUS)] = &EFOCUS;
			CodeFuncArray[static_cast<int>(EVENT_CODE::MOVE)] = &EMOVE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::SIZE)] = &ESIZE;
			CodeFuncArray[static_cast<int>(EVENT_CODE::TEXT)] = &ETEXT;
			CodeFuncArray[static_cast<int>(EVENT_CODE::MENU)] = &EMENU;
			CodeFuncArray[static_cast<int>(EVENT_CODE::ITEM)] = &EITEM;
			CodeFuncArray[static_cast<int>(EVENT_CODE::TIMER)] = &ETIMER;
			CodeFuncArray[static_cast<int>(EVENT_CODE::STATE)] = &ESTATE;
			*/
		}
		
		void WINDOW::ESetProc(){
			if(RegisterFlag == true){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("EntryProc was set");
				#endif
			} else{
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("EntryProc is setting");
				#endif
				if(Unicode.is()){
					if(lpfnWndProc != EntryProcW){
						//本来のプロシージャをDefProcに格納
						DefProc = (WNDPROC)(LONG_PTR)GetWindowLongPtrW(hwnd, GWLP_WNDPROC);
						if(DefProc == 0){
							#ifdef AZ_DEBUG
							DEBUG::error_dialog(NULL, GetTitleW().c_str());
							#endif
						}
						//ProcをEntryProcに変更
						SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)EntryProcW);
					}
				}
				else{
					if(lpfnWndProc != EntryProcA){
						DefProc = (WNDPROC)(LONG_PTR)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
						if(DefProc == 0){
							#ifdef AZ_DEBUG
							DEBUG::error_dialog(NULL, GetTitleW().c_str());
							#endif
						}
						SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)EntryProcA);
					}
				}
			}
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- Set DefProc ----------");
			//DEBUG::DebugConsole::Get_Instance().Log(GetTitleW());
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)DefProc);
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			#endif
		}
		CODE WINDOW::_ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(LOWORD(lp) != GetSize()[0] || HIWORD(lp) != GetSize()[1]){
				SetSize(LOWORD(lp), HIWORD(lp));
				if(DBuff.is() == true){
					HANDLEMAP::Get_Instance().find(hwnd)->Resize(GetSize()[0], GetSize()[1]);
					Rectangle(HANDLEMAP::Get_Instance().find(hwnd)->GetHDC(), 0, 0, GetSize()[0], GetSize()[1]);
				}
				for(auto v : ChildWindow){
					if(v.second->AutoReSize.is() == true){
						SendMessage(v.second->GetHandle(), WM_COMMAND, AZ_RELATIVE_SIZE, 0);
					}
				}
			}
			return DEFAULTEVE;
		}
		
		CODE WINDOW::ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){return 1;}
		CODE WINDOW::ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(GetParentHandle() != nullptr){
				SendMessage(GetParentHandle(), msg, wp, lp);
				return 1;
			}
			if(MessageBoxW(GetParentHandle(), L"終了しますか?", L"確認画面", MB_YESNO) != IDYES) return 0;
			return 1;
		}
		CODE WINDOW::EDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			PostQuitMessage(0);
			return 0;
		}
		CODE WINDOW::ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMOUSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMDI(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCHITTEST(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCMOUSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EEDIT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ECHAR(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EKEY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EQUIT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ESCROLL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EACTIVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EFOCUS(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMOVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ETEXT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMENU(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EITEM(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ETIMER(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ESTATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EBKG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ECLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EDCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EHOLD(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ERELATIVESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		
		
		CODE WINDOW::_ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			return 1;
		}
		CODE WINDOW::_EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			CODE ret;
			
			
			/*
			// https://blog.goo.ne.jp/masaki_goo_2006/e/d3c18365234ffb3383f5c30e32c83cf5
			// ダブル・バッファリングの方法(1) を参照
			*/
			if(DBuff.is() == true){
				HDC hmem = HANDLEMAP::Get_Instance().find(hwnd)->GetHDC();
				ret = EPAINT(hwnd, msg, wp, lp, hmem);
				if(LayoutFuncP != nullptr) ret = LayoutFuncP(hmem);
				
				BitBlt(hdc, 0, 0, GetSize()[0], GetSize()[1], hmem, 0, 0, SRCCOPY);
				
			} else{
				
				ret = EPAINT(hwnd, msg, wp, lp, hdc);
				if(LayoutFuncP != nullptr) ret = LayoutFuncP(hdc);
				
			}
			
			
			EndPaint(hwnd, &ps);
			return ret;
		}
		CODE WINDOW::_ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMOUSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMDI(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ENCDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ENCHITTEST(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ENCMOUSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EEDIT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ECHAR(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EKEY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EQUIT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ESCROLL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EACTIVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EFOCUS(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMOVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ETEXT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMENU(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EITEM(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ESTATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EBKG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ECLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EDCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EHOLD(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ERELATIVESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(DBuff.is() == true) HANDLEMAP::Get_Instance().find(hwnd)->Resize(GetSize()[0], GetSize()[1]);
			return DEFAULTEVE;
		}
		
		
		LRESULT CALLBACK WINDOW::EBack(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(Unicode.is()){
				return CallWindowProcW(DefProc, hwnd, msg, wp, lp);
			}
			else return CallWindowProc(DefProc, hwnd, msg, wp, lp);
		}
		
		CODE WINDOW::_CHILDMSG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(ChildWindow.size() != 0){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("-- Child Size -----------");
				DEBUG::DebugConsole::Get_Instance().Log((int)ChildWindow.size());
				#endif
				
				for(auto v : ChildWindow){
					if((LPVOID)LOWORD(wp) == (LPVOID)v.first){
						#ifdef AZ_DEBUG
						DEBUG::DebugConsole::Get_Instance().Log((LPVOID)LOWORD(wp));
						DEBUG::DebugConsole::Get_Instance().Log((LPVOID)v.first);
						std::wstring tmp = L"pass -> ";
						tmp += v.second->GetTitleW();
						//DEBUG::DebugConsole::Get_Instance().Log(tmp);
						DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
						#endif
						return v.second->CHILDMSG(v.second->GetHandle(), msg, wp, lp);
					}
				}
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
				#endif
			}
			return DEFAULTEVE;
		}
		CODE WINDOW::CustomMsg(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::CHILDMSG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		
		CODE WINDOW::_EVENT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp,
			CODE (WINDOW::*system)(const HWND, const UINT, const WPARAM, const LPARAM),
			CODE (WINDOW::*eve)(const HWND, const UINT, const WPARAM, const LPARAM)){
			
			evep = system;
			(this->*evep)(hwnd, msg, wp, lp);
			evep = eve;
			return (this->*evep)(hwnd, msg, wp, lp);
		}
		
		CODE WINDOW::_ETIMER(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(wp == WM_RBUTTONDOWN || wp == WM_MBUTTONDOWN || wp == WM_LBUTTONDOWN){
				switch(wp){
				case WM_RBUTTONDOWN:
					SendMessage(hwnd, EV_RCLICK, _mouse.wp, _mouse.lp);
					break;
				case WM_MBUTTONDOWN:
					SendMessage(hwnd, EV_MCLICK, _mouse.wp, _mouse.lp);
					break;
				case WM_LBUTTONDOWN:
					SendMessage(hwnd, EV_LCLICK, _mouse.wp, _mouse.lp);
					break;
				}
			}
			return DEFAULTEVE;
		}
		
		void WINDOW::Layout(CODE (*LayoutFunc)(HDC)){
			LayoutFuncP = LayoutFunc;
		}
		
		
		
		void WINDOW::Show(const int flag){
			ShowWindow(hwnd, flag);
			UpdateWindow(hwnd);
		}
		
		bool WINDOW::Enable(const bool flag){
			return EnableWindow(GetHandle(), flag);
		}
		
		
		//修正したい
		int WINDOW::Message(){
			while(1){
				if(Unicode.is()? PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE) : PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
					if(msg.message == WM_QUIT) break;
					TranslateMessage(&msg);
					Unicode.is()? DispatchMessageW(&msg) : DispatchMessage(&msg);
				} else{
					if(_GameLoopP != nullptr){
						_GameLoopP(GameLoopArgs);
						UpdateDisplay();
					}
					if(_WaitP != nullptr) _WaitP(WaitArgs);
					else Wait();
				}
			}
			return (int)msg.wParam;
		}
		
		void WINDOW::GameLoop(void (*_GameLoop)(LPVOID), LPVOID _args){
			_GameLoopP = _GameLoop;
			GameLoopArgs = _args;
		}
		void WINDOW::UpdateDisplay(){
			InvalidateRect(GetHandle(), NULL, true);
			UpdateWindow(GetHandle());
		}
		
		void WINDOW::Wait(void (*_Waitp)(LPVOID), LPVOID _args){
			_WaitP = _Waitp;
			WaitArgs = _args;
		}
		
		void WINDOW::Print(){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("start create");
			DEBUG::DebugConsole::Get_Instance().Log(_ExStyle);
			if(Unicode.is()){
				//DEBUG::DebugConsole::Get_Instance().Log(lpszClassNameW.c_str());
			} else{
				DEBUG::DebugConsole::Get_Instance().Log(lpszClassName.c_str());
			}
			DEBUG::DebugConsole::Get_Instance().Log(_Title.c_str());
			DEBUG::DebugConsole::Get_Instance().Log(_WindowStyle);
			DEBUG::DebugConsole::Get_Instance().Log(GetPos()[0]);
			DEBUG::DebugConsole::Get_Instance().Log(GetPos()[1]);
			DEBUG::DebugConsole::Get_Instance().Log(GetSize()[0]);
			DEBUG::DebugConsole::Get_Instance().Log(GetSize()[1]);
			#endif
		}
		
		MOUSE WINDOW::_mouse;
		
		void WINDOW::FPSLock(int rate){
			_fpstimer.Lockfps(rate);
		}
		void WINDOW::Wait(){
			_fpstimer.countup();
			_fpstimer.calcfps();
			_fpstimer.wait();
		}
		
		void WINDOW::InitLambda(){
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			_WaitP = nullptr;
		}
		
		
		WINDOW::FPSTIMER::FPSTIMER() :
		FrameRate(60), count(0){
			a = b = last = std::chrono::system_clock::now();
			RateTime = 1000.0 / FrameRate;
		}
		void WINDOW::FPSTIMER::wait(){
			a = std::chrono::system_clock::now();
			work_time = a - b;
			
			if(work_time.count() < RateTime){
				sleep_time = std::chrono::duration<double, std::milli>((RateTime - work_time.count()));
				//auto msec = std::chrono::duration<double, std::milli>(1);
				
				timeBeginPeriod(1);
				while(sleep_time.count() >= 0){
					Sleep(1);
					std::chrono::duration<double, std::milli> tmp = std::chrono::system_clock::now() - b;
					sleep_time = std::chrono::duration<double, std::milli>((RateTime - tmp.count()));
				}
				timeEndPeriod(1);
			}
			b = std::chrono::system_clock::now();
			
		}
		void WINDOW::FPSTIMER::calcfps(){
			if(count >= 100){
				a = std::chrono::system_clock::now();
				std::chrono::duration<double, std::micro> delta = a - last;
				
				fps = (double)(1000.0 * count / delta.count()) * 1000.0;
				count = 0;
				last = std::chrono::system_clock::now();
			}
		}
		void WINDOW::FPSTIMER::countup(){
			count++;
		}
		void WINDOW::FPSTIMER::Lockfps(int n){
			FrameRate = n;
		}
	}
}