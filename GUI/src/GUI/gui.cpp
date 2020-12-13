#include"gui.hpp"


namespace AZ{
	namespace GUI{
		
		PROCMAP::PROCMAP(){}
		PROCMAP::~PROCMAP(){}
		
		WINDOW* PROCMAP::find(HWND hwnd){
			std::map<HWND, WINDOW*>::iterator itr = hWndMap.find(hwnd);
			if(itr != hWndMap.end()) return itr->second;
			return nullptr;
		}
		
		bool PROCMAP::Register(HWND hwnd, WINDOW *item){
			return  hWndMap.insert(std::pair<HWND, WINDOW* >(hwnd, item)).second;
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
			_pWindow = w;
			_Unicode = true;
			_DBuff = false;
			_RelativeSize = false;
		}
		WINDOW::MODE::~MODE(){}
		void WINDOW::MODE::Unicode(const bool flag){
			_Unicode = flag;
		}
		void WINDOW::MODE::DBuff(const bool flag){
			_DBuff = flag;
		}
		void WINDOW::MODE::RelativeSize(const bool flag){
			_RelativeSize = flag;
		}
		
		bool WINDOW::MODE::isUnicode(){
			return _Unicode;
		}
		bool WINDOW::MODE::isDBuff(){
			return _DBuff;
		}
		bool WINDOW::MODE::isRelativeSize(){
			return _RelativeSize;
		}
		
		using CODE = int;
		WINDOW* WINDOW::tmp = nullptr;
		WINDOW::WINDOW() : STATE(), Mode(this){
			tmp = this;
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
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			_Title = "Azalea Window";
			_TitleW = L"Azalea Window";
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			
			Border = false;
			Proc = &WINDOW::WindowProc;
			cbSize = sizeof(WNDCLASSEXW);
			lpfnWndProc = EntryProcW;
			DefProc = DefWindowProcW;
			InitCodeArray();
			
			FrameRate = 30;
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
		}
		WINDOW::WINDOW(const int w, const int h) : STATE(w, h), Mode(this){
			tmp = this;
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
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			_Title = "Azalea Window";
			_TitleW = L"Azalea Window";
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			
			Border = false;
			Proc = &WINDOW::WindowProc;
			cbSize = sizeof(WNDCLASSEXW);
			lpfnWndProc = EntryProcW;
			DefProc = DefWindowProcW;

			InitCodeArray();
			
			FrameRate = 30;
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
		}
		
		WINDOW::WINDOW(const int w, const int h, const std::string title) : STATE(w, h), Mode(this){
			Mode.Unicode(false);
			tmp = this;
			cbSize = sizeof(WNDCLASSEX);
			style = CS_HREDRAW | CS_VREDRAW;
			lpfnWndProc = EntryProc;
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
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			_Title = title;
			_TitleW = L"Azalea Window";
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			
			Border = false;
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProcA;
			InitCodeArray();
			
			FrameRate = 30;
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
		}
		WINDOW::WINDOW(const int w, const int h, const std::wstring title) : STATE(w, h), Mode(this){
			tmp = this;
			cbSize = sizeof(WNDCLASSEXW);
			style = CS_HREDRAW | CS_VREDRAW;
			lpfnWndProc = EntryProcW;
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
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			_Title = TEXT("Azalea Window");
			_TitleW = title;
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			
			Border = false;
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProcW;
			InitCodeArray();
			
			FrameRate = 30;
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
		}
		WINDOW::WINDOW(const std::string title) : STATE(), Mode(this){
			Mode.Unicode(false);
			tmp = this;
			cbSize = sizeof(WNDCLASSEX);
			style = CS_HREDRAW | CS_VREDRAW;
			lpfnWndProc = EntryProc;
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
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			_Title = title;
			_TitleW = L"Azalea Window";
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			
			Border = false;
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProcA;
			InitCodeArray();
			
			FrameRate = 30;
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
		}
		WINDOW::WINDOW(const std::wstring title) : STATE(), Mode(this){
			tmp = this;
			cbSize = sizeof(WNDCLASSEXW);
			style = CS_HREDRAW | CS_VREDRAW;
			lpfnWndProc = EntryProcW;
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
			
			_ExStyle = WS_EX_ACCEPTFILES;
			_WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			_Title = TEXT("Azalea Window");
			_TitleW = title;
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			LayoutFuncP = nullptr;
			_GameLoopP = nullptr;
			
			Border = false;
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProcW;
			InitCodeArray();
			
			FrameRate = 30;
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
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
			if(Mode.isUnicode()){
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
					DEBUG::error_dialog(NULL);
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
					DEBUG::error_dialog(NULL);
					#endif
				}
			}
			RegisterFlag = true;
			return *this;
		}
		const WNDCLASSEX WINDOW::GetWcex(){return wcex;}
		//const WNDCLASSEX WINDOW::GetWcexW(){return wcexw;}
		
		LRESULT CALLBACK WINDOW::EntryProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			WINDOW *ptr = PROCMAP::Get_Instance().find(hwnd);
			
			//hash map(window handle, window proc) 
			if(ptr != nullptr){
				if(msg == WM_DESTROY){
					PROCMAP::Get_Instance().Remove(hwnd);
				}
				return ptr->MyProc(hwnd, msg, wp, lp);
			} else{
				if(msg == WM_CREATE || msg == WM_INITDIALOG){
					ptr = (WINDOW*)(((LPCREATESTRUCT)lp)->lpCreateParams);
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)(ptr));
					ptr->SetHandle(hwnd);
					ptr->ECREATE(hwnd, msg, wp, lp);
				}
			}
			//return 0L;
			return DefWindowProc(hwnd, msg, wp, lp);
		}
		LRESULT CALLBACK WINDOW::EntryProcW(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			WINDOW *ptr = PROCMAP::Get_Instance().find(hwnd);
			
			//hash map(window handle, window proc)
			if(ptr != nullptr){
				if(msg == WM_DESTROY){
					PROCMAP::Get_Instance().Remove(hwnd);
				}
				return ptr->MyProc(ptr->GetHandle(), msg, wp, lp);
			} else{
				if(msg == WM_CREATE || msg == WM_INITDIALOG){
					ptr = (WINDOW*)(((LPCREATESTRUCT)lp)->lpCreateParams);
					SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)(ptr));
					ptr->SetHandle(hwnd);
					ptr->ECREATE(hwnd, msg, wp, lp);
				}
			}
			//return 0L;
			return DefWindowProcW(hwnd, msg, wp, lp);
		}
		
		LRESULT WINDOW::MyProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			#ifdef AZ_DEBUG
			std::wstring _str = L"[";
			_str += GetTitleNameW();
			_str += L"] > ";
			_str += CvtMsgCodetowc(msg);
			DEBUG::DebugConsole::Get_Instance().Log(_str);
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
			return SetWindowTextA(GetHandle(), title.c_str());
		}
		bool WINDOW::ChangeTitle(const std::wstring title){
			return SetWindowTextW(GetHandle(), title.c_str());
		}
		
		
		
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
			
			SetWindowPos(hwnd, NULL, 0, 0, _Width, _Height, SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOMOVE);
		}
		
		void WINDOW::ReSizeWindow(const int w, const int h){
			SetSize(w, h);
			SetWindowPos(GetHandle(), 0, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
		}
		
		void WINDOW::Create(){
			if(Mode.isUnicode()){
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
			PROCMAP::Get_Instance().Register(GetHandle(), this);
			if(hwnd == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL);
				#endif
			}
			
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
			_Title = title;
			hwnd = CreateWindowExA(
				_ExStyle,
				lpszClassName.c_str(), _Title.c_str(),
				_WindowStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				GetParentHandle(), NULL, hInstance, this);
			PROCMAP::Get_Instance().Register(GetHandle(), this);
			if(hwnd == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL);
				#endif
			}
			
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
			_TitleW = title;
			hwnd = CreateWindowExW(
				_ExStyle,
				lpszClassNameW.c_str(), _TitleW.c_str(),
				_WindowStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				GetParentHandle(), NULL, hInstance, this);
			PROCMAP::Get_Instance().Register(GetHandle(), this);
			if(hwnd == nullptr){
				#ifdef AZ_DEBUG
				DEBUG::error_dialog(NULL);
				#endif
			}
			ResizeClient();
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
			ch.SetWindowStyle(ch.GetWindowStyle() | WS_CHILD);
			ch.SetMenu(Id);
			ChildWindow.push_back(std::pair<HMENU, WINDOW*>(Id,&ch));
		}
		void WINDOW::SetMenu(const HMENU Id){
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
					if(ERELATIVESIZE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				}
				if(UNIQMSG(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				if(ECOMMAND(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				return 0;
			
			//create
			case WM_CREATE:
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("Proc Called Create");
				#endif
				return ECREATE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			
			//button (throw down)
			case WM_LBUTTONDBLCLK:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_RBUTTONDBLCLK:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MOUSEMOVE:
				return EMOUSE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
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
				return EMDI(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//NC (throw down)
			case WM_NCDESTROY:
				return ENCDESTROY(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//NC HITTEST
			case WM_NCHITTEST:
				return ENCHITTEST(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//NC MOUSE (throw down)
			case WM_NCLBUTTONDBLCLK:
			case WM_NCLBUTTONDOWN:
			case WM_NCLBUTTONUP:
			case WM_NCMBUTTONDBLCLK:
			case WM_NCMBUTTONDOWN:
			case WM_NCMBUTTONUP:
			case WM_NCRBUTTONDBLCLK:
			case WM_NCRBUTTONDOWN:
			case WM_NCRBUTTONUP:
			case WM_NCMOUSEMOVE:
				return ENCMOUSE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//DROP
			case WM_DROPFILES:
				return EFILE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//EDIT BOX or COMBO BOX (throw down)
			case WM_CLEAR:
			case WM_COPY:
			case WM_CUT:
			case WM_PASTE:
				return EEDIT(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//CHAR CODE (throw down)
			case WM_CHAR:
			case WM_DEADCHAR:
			case WM_SYSCHAR:
			case WM_SYSDEADCHAR:
				return ECHAR(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//KEY (throw down)
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				return EKEY(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			case WM_CLOSE:
				return ECLOSE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_DESTROY:
				return EDESTROY(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_QUIT:
				return EQUIT(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//SCROLL (throw down)
			case WM_HSCROLL:
			case WM_VSCROLL:
				return ESCROLL(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//STATE (throw down)
			case WM_ENABLE:
			case WM_SHOWWINDOW:
				return ESTATE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//FOCUS (throw down)
			case WM_KILLFOCUS:
			case WM_SETFOCUS:
				return EFOCUS(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//MOVE
			case WM_MOVE:
				return EMOVE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//SIZE
			case WM_SIZE:
				_ESIZE(hwnd, msg, wp, lp);
				return ESIZE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//TEXT (throw down)
			case WM_SETTEXT:
			case WM_GETTEXT:
			case WM_GETTEXTLENGTH:
				return ENCMOUSE(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			//MENU (throw down)
			case WM_INITMENU:
			case WM_INITMENUPOPUP:
			case WM_MENUCHAR:
			case WM_MENUSELECT:
				return EMENU(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			//ITEM (throw down)
			case WM_MEASUREITEM:
			case WM_DRAWITEM:
				return EITEM(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
				
			case WM_ERASEBKGND:
				if(Mode.isDBuff() == true) return 1;
				return EBKG(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
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
				return ETIMER(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			
			default:
				return CustomMsg(hwnd, msg, wp, lp)? EBack(hwnd, msg, wp, lp) : 0;
			}
			return EBack(hwnd, msg, wp, lp);
		}
		
		void WINDOW::InitCodeArray(){
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
				if(Mode.isUnicode()){
					if(lpfnWndProc != EntryProcW){
						//本来のプロシージャをDefProcに格納
						DefProc = (WNDPROC)(LONG_PTR)GetWindowLongPtrW(hwnd, GWLP_WNDPROC);
						if(DefProc == 0){
							#ifdef AZ_DEBUG
							DEBUG::error_dialog(NULL);
							#endif
						}
						//ProcをEntryProcに変更
						SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)EntryProcW);
					}
				}
				else{
					if(lpfnWndProc != EntryProc){
						DefProc = (WNDPROC)(LONG_PTR)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
						if(DefProc == 0){
							#ifdef AZ_DEBUG
							DEBUG::error_dialog(NULL);
							#endif
						}
						SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)EntryProc);
					}
				}
			}
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("-- Set DefProc ----------");
			DEBUG::DebugConsole::Get_Instance().Log(GetTitleNameW());
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)hwnd);
			DEBUG::DebugConsole::Get_Instance().Log((LPVOID)DefProc);
			DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
			#endif
		}
		
		void WINDOW::_ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(LOWORD(lp) != GetSize()[0] && HIWORD(lp) != GetSize()[1]){
				SetSize(LOWORD(lp), HIWORD(lp));
				for(auto v : ChildWindow){
					if(v.second->Mode.isRelativeSize() == true){
						SendMessage(v.second->GetHandle(), WM_COMMAND, 0 | AZ_RELATIVE_SIZE, 0);
					}
				}
			}
		}
		
		CODE WINDOW::ECREATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::_EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			CODE ret = EPAINT(hwnd, msg, wp, lp);
			if(ret == 1 && LayoutFuncP != nullptr){
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				ret = LayoutFuncP(hdc);
				EndPaint(hwnd, &ps);
			}

			return ret;
		}
		CODE WINDOW::EPAINT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ECLOSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
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
		CODE WINDOW::ERELATIVESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		LRESULT CALLBACK WINDOW::EBack(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			if(Mode.isUnicode()){
				return CallWindowProcW(DefProc, hwnd, msg, wp, lp);
			}
			else return CallWindowProc(DefProc, hwnd, msg, wp, lp);
		}
		
		CODE WINDOW::UNIQMSG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			
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
						tmp += v.second->GetTitleNameW();
						DEBUG::DebugConsole::Get_Instance().Log(tmp);
						DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
						#endif
						return v.second->EVENT(v.second->GetHandle(), msg, wp, lp);
					}
				}
				#ifdef AZ_DEBUG
				DEBUG::DebugConsole::Get_Instance().Log("-------------------------");
				#endif
			}
			return DEFAULTEVE;
		}
		CODE WINDOW::CustomMsg(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		CODE WINDOW::EVENT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return DEFAULTEVE;}
		
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
			if(Mode.isUnicode()){
				while(1){
					if(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)){
						if(msg.message == WM_QUIT) break;
						TranslateMessage(&msg);
						DispatchMessageW(&msg);
					} else{
						if(_GameLoopP != nullptr){
							_GameLoopP(GameLoopArgs);
							
							InvalidateRect(GetHandle(), NULL, true);
							UpdateWindow(GetHandle());
						}
						Wait();
					}
				}
			}
			else{
				while(1){
					if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
						if(msg.message == WM_QUIT) break;
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					} else{
						if(_GameLoopP != nullptr){
							_GameLoopP(GameLoopArgs);
							
							InvalidateRect(GetHandle(), NULL, true);
							UpdateWindow(GetHandle());
						}
						Wait();
					}
				}
			}
			
			
			return (int)msg.wParam;
		}
		
		void WINDOW::GameLoop(void (*_GameLoop)(LPVOID), LPVOID _args){
			_GameLoopP = _GameLoop;
			GameLoopArgs = _args;
		}
		
		void WINDOW::Print(){
			#ifdef AZ_DEBUG
			DEBUG::DebugConsole::Get_Instance().Log("start create");
			DEBUG::DebugConsole::Get_Instance().Log(_ExStyle);
			if(Mode.isUnicode()){
				DEBUG::DebugConsole::Get_Instance().Log(lpszClassNameW.c_str());
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
		
		std::function<long long(void)> WINDOW::CurrentTimeMicro = [](){
			std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
			return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
		};
		
		void WINDOW::FPSLock(int rate){
			FrameRate = rate;
		}
		void WINDOW::Wait(){
			long long Now = CurrentTimeMicro();
			if(WaitToNextTime > Now){
				std::this_thread::sleep_for(std::chrono::microseconds(WaitToNextTime - Now));
			}
			WaitToNextTime = CurrentTimeMicro() + 1000 * 1000 / FrameRate;
		}
	}
}