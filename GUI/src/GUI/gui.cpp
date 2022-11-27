//#define AZ_DEBUG 1
#include"gui.hpp"

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
			}
			*/
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
		
		//////////////////////////////////////////////////////////////////////////////
		
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
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- PROCMAP --------------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (int)hWndMap.size());
			for(auto itr : hWndMap){
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)itr.first);
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)itr.second);
			}
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "");
			#endif
		}
		
		//////////////////////////////////////////////////////////////////////////////
		
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
			//std::cout << "Mode is true" << std::endl;
			state = flag;
		}
		
		bool WINDOW::MODE::is(){
			return state;
		}
		
		//////////////////////////////////////////////////////////////////////////////
		
		WINDOW::EVFLAG::EVFLAG() : sizing(false){}
		
		//////////////////////////////////////////////////////////////////////////////
		
		WREG::WREG(){
			
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				cbSize = sizeof(WNDCLASSEXA);
				lpszMenuName = "AzMenu";
				lpszClassName = "AzWindow";
				hIcon = LoadIconA(NULL , IDI_APPLICATION);
				hIconSm = LoadIconA(NULL , IDI_APPLICATION);
				hCursor = LoadCursorA(NULL, IDC_ARROW);
				DefProc = DefWindowProcA;
				hInstance = GetModuleHandleA(NULL);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				cbSize = sizeof(WNDCLASSEXW);
				lpszMenuName = L"AzMenu";
				lpszClassName = L"AzWindow";
				hIcon = LoadIconW(NULL , (LPCWSTR)IDI_APPLICATION);
				hIconSm = LoadIconW(NULL , (LPCWSTR)IDI_APPLICATION);
				hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
				DefProc = DefWindowProcW;
				hInstance = GetModuleHandleW(NULL);
			#endif
			lpfnWndProc = WINDOW::GetEntry();
			style = CS_HREDRAW | CS_VREDRAW;
			cbClsExtra = 0;
			cbWndExtra = 0;
			hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
		}
		
		bool WREG::Register(){
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
			
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			auto ret = RegisterClassExA(&wcex);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			auto ret = RegisterClassExW(&wcex);
			#endif
			if(!ret){
				// if alrady register class
				if(GetLastError() == ERROR_CLASS_ALREADY_EXISTS){
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_WARNING, lpszClassName.c_str());
					#endif
				}
				else{
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_ERROR, lpszClassName.c_str());
					#endif
					return false;
				}
			}
			return true;
		}
		
		const HWND WREG::GetHandle(){
			return *hwnd;
		}
		
		//window class option
		void WREG::SetSize(const UINT size){ cbSize = size; }
		const UINT WREG::GetSize(){ return cbSize; }
		
		void WREG::SetStyle(const UINT Style){
			style = Style;
			if(GetHandle()) SetStyle(style, GetHandle());
		}
		void WREG::SetStyle(const UINT Style, HWND hwnd){
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				SetWindowLongPtrA(hwnd, GWL_STYLE, Style);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				SetWindowLongPtrW(hwnd, GWL_STYLE, Style);
			#endif
		}
		void WREG::AddStyle(const UINT Style){
			style |= Style;
			if(GetHandle()) AddStyle(style, GetHandle());
		}
		void WREG::AddStyle(const UINT Style, const HWND hwnd){
			SetStyle(Style, hwnd);
		}
		const UINT WREG::GetStyle(){ return style; }
		
		void WREG::SetWndProc(WNDPROC lpProc, HWND hwnd){
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG_PTR)lpProc);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)lpProc);
			#endif
		}
		void WREG::SetWndProc(WNDPROC lpProc){
			lpfnWndProc = lpProc;
			if(GetHandle()) SetWndProc(lpfnWndProc, GetHandle());
		}
		const WNDPROC WREG::GetWndProc(){ return lpfnWndProc; }
		
		void WREG::SetDefProc(const WNDPROC def){ DefProc = def; }
		const WNDPROC WREG::GetDefProc(){ return DefProc; }
		
		void WREG::SetClsExtra(const int CE){ cbClsExtra = CE; }
		const int WREG::GetClsExtra(){ return cbClsExtra; }
		
		void WREG::SetWndExtra(const int WE){ cbWndExtra = WE; }
		const int WREG::GetWndExtra(){ return cbWndExtra; }
		
		void WREG::SetInstance(const HINSTANCE hInst){ hInstance = hInst; }
		const HINSTANCE WREG::GetInstance(){ return hInstance; }
		
		void WREG::SetIcon(HICON Icon){ hIcon = Icon; }
		const HICON WREG::GetIcon(){ return hIcon; }
		
		void WREG::SetIconSm(HICON IconSm){ hIconSm = IconSm; }
		const HICON WREG::GetIconSm(){ return hIconSm; }
		
		void WREG::SetCursor(HCURSOR Cursor){ hCursor = Cursor; }
		const HCURSOR WREG::GetCursor(){ return hCursor; }
		
		void WREG::SetBKGColor(const HBRUSH BG){ hbrBackground = BG; }
		const HBRUSH WREG::GetBKGColor(){ return hbrBackground; }
		
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		void WREG::SetMenuName(const std::string MenuName){ lpszMenuName = MenuName; }
		const std::string WREG::GetMenuName(){ return lpszMenuName; }
		
		void WREG::SetClassName(const std::string ClassName){ lpszClassName = ClassName; }
		const std::string WREG::GetClassName(){ return lpszClassName; }
		
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		void WREG::SetMenuName(const std::wstring MenuName){ lpszMenuName = MenuName; }
		const std::wstring WREG::GetMenuName(){ return lpszMenuName; }
		
		void WREG::SetClassName(const std::wstring ClassName){ lpszClassName = ClassName; }
		const std::wstring WREG::GetClassName(){ return lpszClassName; }
		#endif
		
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		WNDCLASSEX WREG::GetWcex(){ return wcex; }
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		WNDCLASSEXW WREG::GetWcex(){ return wcex; }
		#endif
		
		//////////////////////////////////////////////////////////////////////////////
		
		
		void WINDOW::InitWindowClass(){
			wreg = new WREG();
			
			_ExStyle = /*WS_EX_ACCEPTFILES |*/ WS_EX_OVERLAPPEDWINDOW;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			
			//InitFrameRate(30);
		}
		
		using CODE = int;
		WINDOW* WINDOW::tmp = nullptr;
		WINDOW::WINDOW() :
			STATE(), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this), GPUAPI(this, false),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Borderless(this, false), Proc(&WINDOW::WindowProc), Error(false){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				_Title = "Azalea Window";
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				_Title = L"Azalea Window";
				#endif
				
		}
		WINDOW::WINDOW(const int w, const int h) : 
			STATE(w, h), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this), GPUAPI(this, false),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Borderless(this, false), Proc(&WINDOW::WindowProc), Error(false){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				_Title = "Azalea Window";
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				_Title = L"Azalea Window";
				#endif
		}
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		WINDOW::WINDOW(const int w, const int h, const std::string title) : 
			STATE(w, h), Unicode(this), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this), GPUAPI(this, false),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Borderless(this, false), Proc(&WINDOW::WindowProc), Error(false){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = title;
		}
		WINDOW::WINDOW(const std::string title) : 
			STATE(), Unicode(this), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this), GPUAPI(this, false),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Borderless(this, false), Proc(&WINDOW::WindowProc), Error(false){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = title;
		}
		
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		WINDOW::WINDOW(const int w, const int h, const std::wstring title) : 
			STATE(w, h), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this), GPUAPI(this, false),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Borderless(this, false), Proc(&WINDOW::WindowProc), Error(false){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = title;
		}
		
		WINDOW::WINDOW(const std::wstring title) : 
			STATE(), Unicode(this, true), DBuff(this, false), DBuffDIB(this), DClick(this), AutoReSize(this), GPUAPI(this, false),
			hwnd(nullptr), hparent(nullptr), Menu(NULL), RegisterFlag(false),
			Borderless(this, false), Proc(&WINDOW::WindowProc), Error(false){
				tmp = this;
				
				InitWindowClass();
				InitLambda();
				InitCodeArray();
				
				_Title = title;
		}
		#endif
		
		WINDOW::~WINDOW(){
			
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			if(wreg->GetDefProc() != DefWindowProcA){
				SetWindowLongPtrA(GetHandle(), GWLP_WNDPROC, (LONG_PTR)wreg->GetDefProc());
			}
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			if(wreg->GetDefProc() != DefWindowProcW){
				SetWindowLongPtrW(GetHandle(), GWLP_WNDPROC, (LONG_PTR)wreg->GetDefProc());
			}
			#endif
			
			#ifdef AZ_DEBUG
			if(&(DEBUG::DebugConsole::Get_Instance()) != nullptr) delete &(DEBUG::DebugConsole::Get_Instance());
			#endif
		}
		
		WINDOW::ENTRYPROC WINDOW::GetEntry(){
			return EntryProc;
		}
		
		WINDOW& WINDOW::WClassSize(const UINT Size){				wreg->SetSize(Size);			return *this;}
		WINDOW& WINDOW::WClassStyle(const UINT Style){				wreg->SetStyle(Style);			return *this;}
		WINDOW& WINDOW::WClassWndProc(WNDPROC lpProc){				wreg->SetWndProc(lpProc);		return *this;}
		WINDOW& WINDOW::WClassClsExtra(const int CE){				wreg->SetClsExtra(CE);			return *this;}
		WINDOW& WINDOW::WClassWndExtra(const int WE){				wreg->SetWndExtra(WE);			return *this;}
		WINDOW& WINDOW::WClassInstance(const HINSTANCE hInst){		wreg->SetInstance(hInst);		return *this;}
		WINDOW& WINDOW::WClassIcon(HICON Icon){						wreg->SetIcon(Icon);			return *this;}
		WINDOW& WINDOW::WClassIconSm(HICON IconSm){					wreg->SetIconSm(IconSm);		return *this;}
		WINDOW& WINDOW::WClassCursor(HCURSOR Cursor){				wreg->SetCursor(Cursor);		return *this;}
		WINDOW& WINDOW::WClassBackground(const HBRUSH BG){			wreg->SetBKGColor(BG);			return *this;}
		
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		WINDOW& WINDOW::WClassMenuName(const std::string MenuName){	wreg->SetMenuName(MenuName);	return *this;}
		WINDOW& WINDOW::WClassName(const std::string ClassName){	wreg->SetClassName(ClassName);	return *this;}
		std::string WINDOW::GetClassName(){return wreg->GetClassName();}
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		WINDOW& WINDOW::WClassMenuName(const std::wstring MenuName){wreg->SetMenuName(MenuName);	return *this;}
		WINDOW& WINDOW::WClassName(const std::wstring ClassName){	wreg->SetClassName(ClassName);	return *this;}
		std::wstring WINDOW::GetClassName(){return wreg->GetClassName();}
		#endif
		
		HINSTANCE WINDOW::GetInst(){ return wreg->GetInstance(); }
		
		WINDOW& WINDOW::Register(){
			RegisterFlag = true;
			return *this;
		}
		void WINDOW::_Register(){ if(RegisterFlag) wreg->Register(); }
		
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		const WNDCLASSEX WINDOW::GetWcex(){return wreg->GetWcex(); }
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		const WNDCLASSEXW WINDOW::GetWcex(){return wreg->GetWcex(); }
		#endif
		
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		LRESULT CALLBACK WINDOW::EntryProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			WINDOW *ptr;
			if(HANDLEMAP::Get_Instance().find(hwnd) == nullptr) ptr = nullptr;
			else ptr = HANDLEMAP::Get_Instance().find(hwnd)->GetWINDOW();
			
			//hash map(window handle, window proc) 
			if(ptr != nullptr){
				if(msg == WM_DESTROY) HANDLEMAP::Get_Instance().Remove(hwnd);
				return ptr->MyProc(hwnd, msg, wp, lp);
			} else{
				if(msg == WM_CREATE || msg == WM_INITDIALOG){
					ptr = (WINDOW*)(((LPCREATESTRUCT)lp)->lpCreateParams);
					SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)(ptr));
					ptr->SetHandle(hwnd);
					ptr->_EVENT(hwnd, msg, wp, lp, &_ECREATE, &ECREATE);
					//ptr->ECREATE(hwnd, msg, wp, lp);
				}
			}
			//return 0L;
			return DefWindowProcA(hwnd, msg, wp, lp);
		}
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		LRESULT CALLBACK WINDOW::EntryProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			WINDOW *ptr;
			if(HANDLEMAP::Get_Instance().find(hwnd) == nullptr) ptr = nullptr;
			else ptr = HANDLEMAP::Get_Instance().find(hwnd)->GetWINDOW();
			
			//hash map(window handle, window proc)
			if(ptr != nullptr){
				if(msg == WM_DESTROY) HANDLEMAP::Get_Instance().Remove(hwnd);
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
		#endif
		bool WINDOW::isSysProc(UINT msg){
			switch(msg){
				case WM_DROPFILES:
				
				return true;
			}
			return false;
		}
		LRESULT WINDOW::SysProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			// Singletonオブジェクトに対するメッセージ処理を行う
			
			//EVENT::Get_Instance().Do(hwnd, msg, wp, lp);
			/*
			switch(msg){
			// マウス処理
			
			// ファイル処理
			
				case WM_DROPFILES:
				std::wcout << L"File Drop" << std::endl;
				
				return 0L;
			
			// 音声処理
			
			}
			*/
			// 処理をしなかった
			return 1;
		}
		
		LRESULT WINDOW::MyProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			#ifdef AZ_DEBUG
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
					std::string _str = "[";
					_str += GetTitle();
					_str += "] > ";
					_str += "MSG : ";
					_str += CvtMsgCodetoc(msg);
					_str += " WPARAM : ";
					_str += std::to_string(wp);
					_str += " LPARAM : ";
					_str += std::to_string(lp);
					
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, _str);
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
					std::wstring _str = L"[";
					_str += GetTitle();
					_str += L"] > ";
					_str += L"MSG : ";
					_str += CvtMsgCodetowc(msg);
					_str += L" WPARAM : ";
					_str += std::to_wstring(wp);
					_str += L" LPARAM : ";
					_str += std::to_wstring(lp);
					std::wcout << _str << std::endl;
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, _str);
				#endif
			#endif
			SysProc(hwnd, msg, wp, lp);
			return  (this->WindowProc)(hwnd, msg, wp, lp);
		}
		
		#define SET_CLASS_STYLE(f, s) \
			if((f)) wreg->SetStyle(wreg->GetStyle() | (s)); \
			else wreg->SetStyle(wreg->GetStyle() & ~(s));
		
		#define SET_WINDOW_STYLE(f, s) \
			if((f)) _WindowStyle |= (s); \
			else _WindowStyle &= ~(s);
			
		
		
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
			SET_CLASS_STYLE(v, CS_VREDRAW);
			SET_CLASS_STYLE(h, CS_HREDRAW);
			return *this;
		}
		WINDOW& WINDOW::setDBLCLKS(bool f){
			SET_CLASS_STYLE(f, CS_DBLCLKS);
			return *this;
		}
		WINDOW& WINDOW::setDC(bool cl, bool own, bool parent){
			SET_CLASS_STYLE(cl, CS_CLASSDC);
			SET_CLASS_STYLE(own, CS_OWNDC);
			SET_CLASS_STYLE(parent, CS_PARENTDC);
			return *this;
		}
		WINDOW& WINDOW::setGLOBAL(bool f){
			SET_CLASS_STYLE(f, CS_GLOBALCLASS);
			return *this;
		}
		WINDOW& WINDOW::setBORDER(bool f){
			SET_WINDOW_STYLE(f, WS_BORDER);
			return *this;
		}
		WINDOW& WINDOW::setCAPTION(bool f){
			SET_WINDOW_STYLE(f, WS_CAPTION);
			return *this;
		}
		WINDOW& WINDOW::setCHILD(bool f){
			SET_WINDOW_STYLE(f, WS_CHILD);
			return *this;
		}
		WINDOW& WINDOW::setCLIPCHILDREN(bool f){
			SET_WINDOW_STYLE(f, WS_CLIPCHILDREN);
			return *this;
		}
		WINDOW& WINDOW::setCLIPSIBLINGS(bool f){
			SET_WINDOW_STYLE(f, WS_CLIPSIBLINGS);
			return *this;
		}
		WINDOW& WINDOW::setDISABLED(bool f){
			SET_WINDOW_STYLE(f, WS_DISABLED);
			return *this;
		}
		WINDOW& WINDOW::setDLGFRAME(bool f){
			SET_WINDOW_STYLE(f, WS_DLGFRAME);
			return *this;
		}
		WINDOW& WINDOW::setGROUP(bool f){
			SET_WINDOW_STYLE(f, WS_GROUP);
			return *this;
		}
		WINDOW& WINDOW::setSCROLL(bool h, bool v){
			SET_WINDOW_STYLE(h, WS_HSCROLL);
			SET_WINDOW_STYLE(v, WS_VSCROLL);
			return *this;
		}
		WINDOW& WINDOW::setCAPTIONBOX(bool min, bool max, bool close){
			SET_WINDOW_STYLE(min, WS_MINIMIZEBOX);
			SET_WINDOW_STYLE(max, WS_MAXIMIZEBOX);
			SET_WINDOW_STYLE(close, CS_NOCLOSE);
			return *this;
		}
		WINDOW& WINDOW::setMIN(bool f){
			SET_WINDOW_STYLE(f, WS_MINIMIZE);
			return *this;
		}
		WINDOW& WINDOW::setMAX(bool f){
			SET_WINDOW_STYLE(f, WS_MAXIMIZE);
			return *this;
		}
		WINDOW& WINDOW::setTABSTOP(bool f){
			SET_WINDOW_STYLE(f, WS_TABSTOP);
			return *this;
		}
		WINDOW& WINDOW::setPOPUP(bool f){
			SET_WINDOW_STYLE(f, WS_POPUP);
			return *this;
		}
		WINDOW& WINDOW::setVISIBLE(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setTITLEDWINDOW(bool f){
			SET_WINDOW_STYLE(f, WS_OVERLAPPEDWINDOW);
			return *this;
		}
		WINDOW& WINDOW::setABSPOTION(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setACCEPTFILES(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setCLIENTEDGE(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setCONTEXTHELP(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setLEFTSCROLLBAR(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setMDICHILD(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setNOPARENTNOTIFY(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setTOOLWINDOW(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setTOPMOST(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		WINDOW& WINDOW::setTRANSPARENT(bool f){
			SET_WINDOW_STYLE(f, WS_VISIBLE);
			return *this;
		}
		
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		WINDOW& WINDOW::SetTitle(const std::string title){
			_Title = title;
			return *this;
		}
		std::string WINDOW::GetTitle(){
			return _Title;
		}
		bool WINDOW::ChangeTitle(const std::string title){
			_Title = title;
			return SetWindowTextA(GetHandle(), _Title.c_str());
		}
		
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		WINDOW& WINDOW::SetTitle(const std::wstring title){
			_Title = title;
			return *this;
		}
		std::wstring WINDOW::GetTitle(){
			return _Title;
		}
		bool WINDOW::ChangeTitle(const std::wstring title){
			_Title = title;
			return SetWindowTextW(GetHandle(), _Title.c_str());
		}
		#endif
		
		
		WINDOW& WINDOW::WindowSize(const int w, const int h){
			SetSize(w, h);
			return *this;
		}
		WINDOW& WINDOW::WindowPos(const int x, const int y){
			SetPos(x, y);
			return *this;
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
		void WINDOW::ResizeClient(){
			RECT wrect, crect;
			
			if(GetParentHandle() == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"Resize");
				#endif
				
				if(Borderless.is()){
					GetWindowRect(GetHandle(), &wrect);
					
					POINT pt;
					
					int tmpx = GetSystemMetrics(SM_CXFRAME) - GetSystemMetrics(SM_CXBORDER);
					int tmpy = GetSystemMetrics(SM_CYFRAME) - GetSystemMetrics(SM_CYBORDER);
					
					
					pt.x = wrect.left + tmpx;
					pt.y = wrect.top + tmpy;
					ScreenToClient(GetHandle(), &pt);
					SetWindowPos(
						GetHandle(), nullptr, pt.x, pt.y,
						(wrect.right - wrect.left) - tmpx * 2,
						(wrect.bottom - wrect.top) - tmpy * 2,
						SWP_DRAWFRAME | SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);
					
					#if AZ_STR_ENCODE == STR_ENCODE_SJIS
					SetWindowLongA(GetHandle(), GWL_STYLE, WS_POPUP | WS_BORDER);
					#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
					SetWindowLongW(GetHandle(), GWL_STYLE, WS_POPUP | WS_BORDER);
					#endif
					
				} else{
					
					GetWindowRect(GetHandle(), &wrect);
					GetClientRect(GetHandle(), &crect);
					
					int _Width = (wrect.right - wrect.left) - (crect.right - crect.left) + GetSize()[0];
					int _Height = (wrect.bottom - wrect.top) - (crect.bottom - crect.top) + GetSize()[1];
					
					SetWindowPos(GetHandle(), HWND_TOP, 0, 0, _Width, _Height, SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);
				}
			}
		}
		
		void WINDOW::ReSizeWindow(const int w, const int h){
			SetSize(w, h);
			SetWindowPos(GetHandle(), 0, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
		}
		
		bool WINDOW::Create(){
			_Register();
			
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				SetHandle(CreateWindowExA(
					_ExStyle,
					wreg->GetClassName().c_str(), _Title.c_str(),
					_WindowStyle,
					GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
					GetParentHandle(), Menu, GetInst(), this));
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				SetHandle(CreateWindowExW(
					_ExStyle,
					wreg->GetClassName().c_str(), _Title.c_str(),
					_WindowStyle,
					GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
					GetParentHandle(), Menu, GetInst(), this));
			#endif
			
			
			if(GetHandle() == nullptr){
				if(GetLastError() == ERROR_CLASS_DOES_NOT_EXIST){
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_WARNING, GetTitle().c_str());
					#endif
				} else{
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_ERROR, GetTitle().c_str());
					#endif
				}
				
				
				Error = true;
				return false;
			}
			
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------- Create Info --------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"HWND    : ") + std::to_wstring((LONGLONG)GetHandle()));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"TITLE   : ") + GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"CLASS   : ") + GetClassName());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"POS-X   : ") + std::to_wstring(GetPos()[0]));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"POS-Y   : ") + std::to_wstring(GetPos()[1]));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"WIDTH   : ") + std::to_wstring(GetSize()[0]));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"HEIGHT  : ") + std::to_wstring(GetSize()[1]));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"PARENT  : ") + std::to_wstring((LONGLONG)GetParentHandle()));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-----------------------------");
			#endif
			
			//PROCMAP::Get_Instance().Register(GetHandle(), this);
			HANDLEMAP::Get_Instance().Register(GetHandle(), this);
			
			ResizeClient();
			if(GetParentHandle() == nullptr){
				//ResizeClient();
				ESetProc();
			}
			if(ChildWindow.size() != 0){
				for(auto v : ChildWindow){
					v.second->SetParentHandle(GetHandle());
					v.second->SetParent(this);
					v.second->Create();
					v.second->ESetProc();
				}
			}
			return true;
		}
		#if AZ_STR_ENCODE == STR_ENCODE_SJIS
		bool WINDOW::Create(const std::string title){
			_Register();
			
			_Title = title;
			SetHandle(CreateWindowExA(
				_ExStyle,
				wreg->GetClassName().c_str(), _Title.c_str(),
				_WindowStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				GetParentHandle(), Menu, GetInst(), this));
			if(GetHandle() == nullptr){
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
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Create Child");
				#endif
				for(auto v : ChildWindow){
					v.second->SetParentHandle(GetHandle());
					v.second->SetParent(this);
					v.second->Create();
					v.second->ESetProc();
					
				}
			}
			return true;
		}
		#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
		bool WINDOW::Create(const std::wstring title){
			_Register();
			
			_Title = title;
			SetHandle(CreateWindowExW(
				_ExStyle,
				wreg->GetClassName().c_str(), _Title.c_str(),
				_WindowStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				GetParentHandle(), Menu, GetInst(), this));
			if(GetHandle() == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL, GetTitle().c_str());
				#endif
			}
			//PROCMAP::Get_Instance().Register(GetHandle(), this);
			HANDLEMAP::Get_Instance().Register(GetHandle(), this);
			
			if(GetParentHandle() == nullptr){
				ResizeClient();
				ESetProc();
			}
			if(ChildWindow.size() != 0){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Create Child");
				#endif
				//for(auto v : ChildWindow){
				for(auto v = ChildWindow.end(); v != ChildWindow.begin(); --v){
					v->second->SetParentHandle(GetHandle());
					v->second->SetParent(this);
					v->second->Create();
					v->second->ESetProc();
					
				}
			}
			return true;
		}
		#endif
		void WINDOW::Child(WINDOW& ch, const HMENU Id){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Set Child");
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
			return Parent == nullptr? *this : *Parent;
		}
		
		WINDOW& WINDOW::GetTopParent(){
			WINDOW *TopParentWindow = this;
			while(TopParentWindow->Parent != nullptr) TopParentWindow = TopParentWindow->Parent;
			/*
			if(TopParentWindow == nullptr){
				std::wcout << L"nullptr" << std::endl;
				MessageBoxW(NULL, L"nullptr", L"nullptr", MB_OK);
			} else{
				std::wcout << TopParentWindow << std::endl;
				MessageBoxW(NULL, L"nullptr", std::to_wstring((UINT64)TopParentWindow).c_str(), MB_OK);
			}
			*/
			return *TopParentWindow;
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
				
				// MENU_MSG or COMMAND_MSG
				/*
				ハンドルとメッセージが違うのは子ウィンドウのコマンドのみ
				if(メッセージクラスからfor文で探査)->ret = _EVENT(hwnd, msg, wp, lp, &_EMCOMMAND, &EMCOMMAND)
				else ret = _EVENT(hwnd, msg, wp, lp, &_ECOMMAND, &ECOMMAND)
				return ret ? EBack(hwnd, msg, wp, lp) : 0;
				*/
				//if(_EVENT(hwnd, msg, wp, lp, &_CHILDMSG, &CHILDMSG)) return EBack(hwnd, msg, wp, lp);
				if(_EVENT(hwnd, msg, wp, lp, &_ECOMMAND, &ECOMMAND)) return EBack(hwnd, msg, wp, lp);
				return 0;
				
			//CREATE
			case WM_CREATE:
				#if AZ_DEBUG > 0
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Proc Called Create");
				#endif
				return _EVENT(hwnd, msg, wp, lp, &_ECREATE, &ECREATE)? EBack(hwnd, msg, wp, lp) : 0;
			
			
			//MOUSE (throw down)
			case WM_LBUTTONDBLCLK:
			case WM_MBUTTONDBLCLK:
			case WM_RBUTTONDBLCLK:
				return _EVENT(hwnd, msg, wp, lp, &_EDCLICK, &EDCLICK)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_NCLBUTTONDBLCLK:
			case WM_NCMBUTTONDBLCLK:
			case WM_NCRBUTTONDBLCLK:
				return _EVENT(hwnd, msg, wp, lp, &_ENCDCLICK, &ENCDCLICK)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
				SetTimer(GetHandle(), msg, GetDoubleClickTime(), NULL);
				_mouse.wp = wp;
				_mouse.lp = lp;
				return _EVENT(hwnd, msg, wp, lp, &_EMDOWN, &EMDOWN)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_NCLBUTTONDOWN:
			case WM_NCMBUTTONDOWN:
			case WM_NCRBUTTONDOWN:
				SetTimer(GetHandle(), msg, GetDoubleClickTime(), NULL);
				_mouse.wp = wp;
				_mouse.lp = lp;
				return _EVENT(hwnd, msg, wp, lp, &_ENCMDOWN, &ENCMDOWN)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
				return _EVENT(hwnd, msg, wp, lp, &_EMUP, &EMUP)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_NCLBUTTONUP:
			case WM_NCMBUTTONUP:
			case WM_NCRBUTTONUP:
				return _EVENT(hwnd, msg, wp, lp, &_ENCMUP, &ENCMUP)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_MOUSEMOVE:
				return _EVENT(hwnd, msg, wp, lp, &_EMMOVE, &EMMOVE)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_MOUSEWHEEL:
				return _EVENT(hwnd, msg, wp, lp, &_EMWHEEL, &EMWHEEL)? EBack(hwnd, msg, wp, lp) : 0;
			
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
				MessageBoxW(NULL, L"Drop", L"File", MB_OK);
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
			case WM_SIZING:
			//case WM_ENTERSIZEMOVE:
			//case WM_EXITSIZEMOVE:
				return _EVENT(hwnd, msg, wp, lp, &_ESIZE, &ESIZE)? EBack(hwnd, msg, wp, lp) : 0;
			
			//TEXT (throw down)
			case WM_SETTEXT:
			case WM_GETTEXT:
			case WM_GETTEXTLENGTH:
				return _EVENT(hwnd, msg, wp, lp, &_ETEXT, &ETEXT)? EBack(hwnd, msg, wp, lp) : 0;
			
			//MENU (throw down)
			case WM_INITMENU:
			case WM_INITMENUPOPUP:
			case WM_MENUCHAR:
			case WM_MENUSELECT:
				return _EVENT(hwnd, msg, wp, lp, &_EMENU, &EMENU)? EBack(hwnd, msg, wp, lp) : 0;
			
			//MENU COMMAND
			case WM_MENUCOMMAND:
				return _EVENT(hwnd, msg, wp, lp, &_EMCOMMAND, &EMCOMMAND)? EBack(hwnd, msg, wp, lp) : 0;
				
			//ITEM (throw down)
			case WM_MEASUREITEM:
			case WM_DRAWITEM:
				return _EVENT(hwnd, msg, wp, lp, &_EITEM, &EITEM)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_ERASEBKGND:
				if(DBuff.is() == true || DBuffDIB.is() == true){
					//HDC hmem = HANDLEMAP::Get_Instance().find(hwnd)->GetHDC();
					//Rectangle(hmem, 0, 0, GetSize()[0], GetSize()[1]);
					return 1;
				}
				return _EVENT(hwnd, msg, wp, lp, &_EBKG, &EBKG)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_PAINT:
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, msg);
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
			#ifdef AZ_DEBUG
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			WNDPROC oldEntryProc = (WNDPROC)(LONG_PTR)GetWindowLongPtrA(GetHandle(), GWLP_WNDPROC);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			WNDPROC oldEntryProc = (WNDPROC)(LONG_PTR)GetWindowLongPtrW(GetHandle(), GWLP_WNDPROC);
			#endif
			#endif
			
			if(RegisterFlag == true){
				#ifdef AZ_DEBUG
				//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"エントリープロシージャは設定済みです");
				#endif
			} else{
				
				
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				if(wreg->GetWndProc() != EntryProc){
					wreg->SetDefProc((WNDPROC)(LONG_PTR)GetWindowLongPtrA(GetHandle(), GWLP_WNDPROC));
					if(wreg->GetDefProc() == 0){
						#ifdef AZ_DEBUG
						DEBUG::error_dialog(NULL, GetTitle().c_str());
						#endif
					}
					SetWindowLongPtrA(GetHandle(), GWLP_WNDPROC, (LONG_PTR)EntryProc);
				}else{
					auto tmp = (WNDPROC)(LONG_PTR)GetWindowLongPtrA(GetHandle(), GWLP_WNDPROC);
					if(tmp != EntryProc){
						#ifdef AZ_DEBUG
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitleW());
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Not match");
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)EntryProc);
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)tmp);
						#endif
					}
				}
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				if(wreg->GetWndProc() != EntryProc){
					//本来のプロシージャをDefProcに格納
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"EntryProcに設定しています");
					#endif
					wreg->SetDefProc((WNDPROC)(LONG_PTR)GetWindowLongPtrW(GetHandle(), GWLP_WNDPROC));
					if(wreg->GetDefProc() == 0){
						#ifdef AZ_DEBUG
						DEBUG::error_dialog(NULL, GetTitle().c_str());
						#endif
					}
					//ProcをEntryProcに変更
					SetWindowLongPtrW(GetHandle(), GWLP_WNDPROC, (LONG_PTR)EntryProc);
				} else{
					auto tmp = (WNDPROC)(LONG_PTR)GetWindowLongPtrW(GetHandle(), GWLP_WNDPROC);
					if(tmp != EntryProc){
						#ifdef AZ_DEBUG
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitleW());
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "Not match");
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)EntryProc);
						//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)tmp);
						#endif
					}
				}
				#ifdef AZ_DEBUG
				//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"GetWindowLongPtrW");
				//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetTitleW());
				//DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)oldEntryProc);
				#endif
				#endif
			}
			
			#if AZ_DEBUG > 0
			WNDPROC newEntryProc = (WNDPROC)(LONG_PTR)GetWindowLongPtrW(GetHandle(), GWLP_WNDPROC);
			MessageBoxW(nullptr, L"SetProc", L"SetProc", MB_OK);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"-------- Entry Procedure --------");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"TITLE        : ") + GetTitle());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"HANDLE       : ") + std::to_wstring((long long)GetHandle()));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"OldEntryProc : ") + std::to_wstring((long long)oldEntryProc));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"NowEntryProc : ") + std::to_wstring((long long)newEntryProc));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"DefProc      : ") + std::to_wstring((long long)wreg->GetDefProc()));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"EntryProc   : ") + std::to_wstring((long long)EntryProc));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, std::wstring(L"lpfnWndProc  : ") + std::to_wstring((long long)wreg->GetWndProc()));
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
			#endif
		}
		CODE WINDOW::_ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			static bool Maxim = false;
			
			// 最大化されたらWS_EX_CLIENTEDGEを外す
			if(GetParentHandle() == nullptr){
				if(wp == SIZE_MAXIMIZED){
					//Maxim = true;
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"MAXIMIZED");
					#endif
					//MessageBoxW(NULL, L"MAXIMIZED", L"CAPTION", MB_OK);
					//SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetExStyle() | WS_EX_CLIENTEDGE);
				}
				if(wp == SIZE_RESTORED /*&& Maxim*/){
					//Maxim = false;
					#ifdef AZ_DEBUG
					DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"RESTORED");
					#endif
					#if AZ_STR_ENCODE == STR_ENCODE_SJIS
					SetWindowLongPtrA(hwnd, GWL_EXSTYLE, GetExStyle() & ~WS_EX_CLIENTEDGE);
					#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
					SetWindowLongPtrW(hwnd, GWL_EXSTYLE, GetExStyle() & ~WS_EX_CLIENTEDGE);
					#endif
					SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, (SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED));
				}
			}
			
			if(LOWORD(lp) != GetSize()[0] || HIWORD(lp) != GetSize()[1]){
				SetSize(LOWORD(lp), HIWORD(lp));
				if(DBuff.is() == true){
					HANDLEMAP::Get_Instance().find(hwnd)->Resize(GetSize()[0], GetSize()[1]);
					Rectangle(HANDLEMAP::Get_Instance().find(hwnd)->GetHDC(), 0, 0, GetSize()[0], GetSize()[1]);
				}
				for(auto v : ChildWindow){
					if(v.second->AutoReSize.is() == true){
						#if AZ_STR_ENCODE == STR_ENCODE_SJIS
						SendMessageA(v.second->GetHandle(), WM_COMMAND, AZ_RELATIVE_SIZE, 0);
						#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
						SendMessageW(v.second->GetHandle(), WM_COMMAND, AZ_RELATIVE_SIZE, 0);
						#endif
					}
				}
			}
			return DEFAULTEVE;
		}
		
		CODE WINDOW::ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			InvalidateRect(hwnd, NULL, true);
			return 1;
		}
		CODE WINDOW::EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp, HDC hdc){return DEFAULTEVE;}
		CODE WINDOW::ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(GetParentHandle() != nullptr){
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				SendMessageA(GetParentHandle(), msg, wp, lp);
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				SendMessageW(GetParentHandle(), msg, wp, lp);
				#endif
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
		CODE WINDOW::EMMOVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
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
		CODE WINDOW::EMCOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EITEM(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ETIMER(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ESTATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EFILE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EBKG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ECLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EDCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCDCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ENCMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EHOLD(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::ERELATIVESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EMWHEEL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		
		
		CODE WINDOW::_ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"WM_CREATE");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)hwnd);
			#endif
			
			return 1;
		}
		CODE WINDOW::_EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			return Render(hwnd, msg, wp, lp);
		}
		
		CODE WINDOW::Render(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			CODE ret;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, L"WM_PAINT");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, HANDLEMAP::Get_Instance().find(hwnd)->GetWINDOW()->GetTitle().c_str());
			#endif
			
			/*
			// https://blog.goo.ne.jp/masaki_goo_2006/e/d3c18365234ffb3383f5c30e32c83cf5
			// ダブル・バッファリングの方法(1) を参照
			*/
			if(DBuff.is() == true){
				HDC hmem = HANDLEMAP::Get_Instance().find(hwnd)->GetHDC();
				ret = EPAINT(hwnd, msg, wp, lp, hmem);
				if(LayoutFuncP != nullptr) ret = LayoutFuncP(hmem);
				
				if(!GPUAPI.is()) BitBlt(hdc, 0, 0, GetSize()[0], GetSize()[1], hmem, 0, 0, SRCCOPY);
			} else{
				ret = GPUAPI.is() ? STOPEVE : EPAINT(hwnd, msg, wp, lp, hdc);
				if(LayoutFuncP != nullptr) ret = LayoutFuncP(hdc);
			}
			
			EndPaint(hwnd, &ps);
			
			return ret;
		}
		
		CODE WINDOW::_ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			// 子ウィンドウで定義されたメッセージなら子ウィンドウにメッセージを投げる
			if(ChildWindow.size() != 0){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Child Size -----------");
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (int)ChildWindow.size());
				#endif
				
				for(auto v : ChildWindow){
					if((LPVOID)LOWORD(wp) == (LPVOID)v.first){
						#ifdef AZ_DEBUG
						DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)LOWORD(wp));
						DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)v.first);
						std::wstring tmp = L"pass -> ";
						tmp += v.second->GetTitle();
						//DEBUG::DebugConsole::Get_Instance().Log(tmp);
						DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
						#endif
						return v.second->ECOMMAND(v.second->GetHandle(), msg, wp, lp);
					}
				}
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
				#endif
			}
			return DEFAULTEVE;
		}
		CODE WINDOW::_EMCOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMMOVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
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
		CODE WINDOW::_ENCCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EDCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ENCDCLICK(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			//MessageBoxW(NULL, std::to_wstring((long long)hwnd).c_str(), L"UP", MB_OK);
			/*
			if(EvFlag.sizing){
				SendMessage(hwnd, AZ_RESIZE, 0, 0);
				MessageBoxW(NULL, L"RESIZE", L"OK", MB_OK);
				EvFlag.sizing = false;
			}*/
			return DEFAULTEVE;
		}
		CODE WINDOW::_ENCMUP(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			/*
			MessageBoxW(NULL, L"NCMOUSE", L"UP", MB_OK);
			if(EvFlag.sizing){
				SendMessage(hwnd, AZ_RESIZE, 0, 0);
				MessageBoxW(NULL, L"RESIZE", L"OK", MB_OK);
				EvFlag.sizing = false;
			}*/
			return DEFAULTEVE;
		}
		CODE WINDOW::_EMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ENCMDOWN(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_EHOLD(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::_ERELATIVESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(DBuff.is() == true) HANDLEMAP::Get_Instance().find(hwnd)->Resize(GetSize()[0], GetSize()[1]);
			return DEFAULTEVE;
		}
		CODE WINDOW::_EMWHEEL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		
		LRESULT CALLBACK WINDOW::EBack(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			return CallWindowProcA(wreg->GetDefProc(), hwnd, msg, wp, lp);
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			return CallWindowProcW(wreg->GetDefProc(), hwnd, msg, wp, lp);
			#endif
		}
		
		CODE WINDOW::_CHILDMSG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(ChildWindow.size() != 0){
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-- Child Size -----------");
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (int)ChildWindow.size());
				#endif
				
				for(auto v : ChildWindow){
					if((LPVOID)LOWORD(wp) == (LPVOID)v.first){
						#ifdef AZ_DEBUG
						DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)LOWORD(wp));
						DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, (LPVOID)v.first);
						std::wstring tmp = L"pass -> ";
						tmp += v.second->GetTitle();
						//DEBUG::DebugConsole::Get_Instance().Log(tmp);
						DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
						#endif
						return v.second->CHILDMSG(v.second->GetHandle(), msg, wp, lp);
					}
				}
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "-------------------------");
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
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				switch(wp){
				case WM_RBUTTONDOWN:
					SendMessageA(hwnd, EV_RCLICK, _mouse.wp, _mouse.lp);
					break;
				case WM_MBUTTONDOWN:
					SendMessageA(hwnd, EV_MCLICK, _mouse.wp, _mouse.lp);
					break;
				case WM_LBUTTONDOWN:
					SendMessageA(hwnd, EV_LCLICK, _mouse.wp, _mouse.lp);
					break;
				}
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				switch(wp){
				case WM_RBUTTONDOWN:
					SendMessageW(hwnd, EV_RCLICK, _mouse.wp, _mouse.lp);
					break;
				case WM_MBUTTONDOWN:
					SendMessageW(hwnd, EV_MCLICK, _mouse.wp, _mouse.lp);
					break;
				case WM_LBUTTONDOWN:
					SendMessageW(hwnd, EV_LCLICK, _mouse.wp, _mouse.lp);
					break;
				}
				#endif
			}
			return DEFAULTEVE;
		}
		
		void WINDOW::Layout(CODE (*LayoutFunc)(HDC)){
			LayoutFuncP = LayoutFunc;
		}
		
		
		
		void WINDOW::Show(const int flag){
			ShowWindow(GetHandle(), flag);
			UpdateWindow(GetHandle());
		}
		
		bool WINDOW::Enable(const bool flag){
			return EnableWindow(GetHandle(), flag);
		}
		
		
		//修正したい
		int WINDOW::Message(){
			BOOL res;
			while(1){
				if(Error){
					MessageBoxW(NULL, L"Error", L"Error", MB_OK);
					return 0;
				}
				
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
				res = PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
				res = PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE);
				#endif
				if(res){
					if(msg.message == WM_QUIT) break;
					TranslateMessage(&msg);
				
				#if AZ_STR_ENCODE == STR_ENCODE_SJIS
					DispatchMessageA(&msg);
				#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
					DispatchMessageW(&msg);
				#endif
				} else{
					if(_GameLoopP != nullptr){
						_GameLoopP(GameLoopArgs);
						if(GPUAPI.is() == false) UpdateDisplay();
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
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, "start create");
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, _ExStyle);
			if(Unicode.is()){
				//DEBUG::DebugConsole::Get_Instance().Log(lpszClassNameW.c_str());
			} else{
				DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, wreg->GetClassName().c_str());
			}
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, _Title.c_str());
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, _WindowStyle);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetPos()[0]);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetPos()[1]);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetSize()[0]);
			DEBUG::DebugConsole::Get_Instance().Log(DEBUG::DebugConsole::ID_NONE, GetSize()[1]);
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