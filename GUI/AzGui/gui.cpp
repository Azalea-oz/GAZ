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
		
		void PROCMAP::Register(HWND hwnd, WINDOW *item){
			hWndMap.insert(std::pair<HWND, WINDOW* >(hwnd, item));
		}
		
		void PROCMAP::Remove(HWND hwnd){
			std::map<HWND, WINDOW*>::iterator itr = hWndMap.find(hwnd);
			if(itr != hWndMap.end()){
				hWndMap.erase(itr);
			}
		}
		
		
		
		
		
		using CODE = int;
		WINDOW* WINDOW::tmp = nullptr;
		WINDOW::WINDOW() : STATE(){
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
			
			PAINT::IMGPAINT::Get_Instance();
			hinst = GetModuleHandle(NULL);
			ExStyle = WS_EX_ACCEPTFILES;
			WStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			WTitle = TEXT("Azalea Window");
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProc;
			InitCodeArray();
		}
		WINDOW::WINDOW(const int w, const int h) : STATE(w, h){
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
			
			PAINT::IMGPAINT::Get_Instance();
			hinst = GetModuleHandle(NULL);
			ExStyle = WS_EX_ACCEPTFILES;
			WStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			WTitle = TEXT("Azalea Window");
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProc;
			InitCodeArray();
		}
		
		WINDOW::WINDOW(const int w, const int h, const std::string title) : STATE(w, h){
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
			
			PAINT::IMGPAINT::Get_Instance();
			hinst = GetModuleHandle(NULL);
			ExStyle = WS_EX_ACCEPTFILES;
			WStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			WTitle = title;
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProc;
			InitCodeArray();
		}
		WINDOW::WINDOW(const std::string title) : STATE(){
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
			
			PAINT::IMGPAINT::Get_Instance();
			hinst = GetModuleHandle(NULL);
			ExStyle = WS_EX_ACCEPTFILES;
			WStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			WTitle = title;
			
			Menu = NULL;
			hwnd = nullptr;
			hparent = nullptr;
			
			RegisterFlag = false;
			
			Proc = &WINDOW::WindowProc;
			DefProc = DefWindowProc;
			InitCodeArray();
		}
		WINDOW::~WINDOW(){
			PAINT::IMGPAINT::Destroy();
			if(&(DEBUG::DebugConsole::Get_Instance()) != nullptr) delete &(DEBUG::DebugConsole::Get_Instance());
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
		WINDOW& WINDOW::WClassName(const std::string ClassName){	lpszClassName = ClassName;	return *this;}
		
		std::string WINDOW::GetClassName(){return lpszClassName;}
		
		WINDOW& WINDOW::Register(){
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
				DEBUG::error_dialog(NULL);
			}
			RegisterFlag = true;
			return *this;
		}
		const WNDCLASSEX WINDOW::GetWcex(){return wcex;}
		
		LRESULT CALLBACK WINDOW::EntryProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			WINDOW *ptr = PROCMAP::Get_Instance().find(hwnd);
			
			//hash map(window handle, window proc) 
			if(ptr != nullptr){
				if(msg == WM_DESTROY){
					PROCMAP::Get_Instance().Remove(hwnd);
				}
				return ptr->MyProc(hwnd, msg, wp, lp);}
			else{
				if(msg == WM_CREATE || msg == WM_INITDIALOG){
					ptr = (WINDOW*)(((LPCREATESTRUCT)lp)->lpCreateParams);
					SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)(ptr));
					ptr->SetHandle(hwnd);
				}
			}
			//return 0L;
			return DefWindowProc(hwnd, msg, wp, lp);
		}
		
		LRESULT WINDOW::MyProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			return (this->WindowProc)(hwnd, msg, wp, lp);
		}
		
		WINDOW& WINDOW::WindowExStyle(const DWORD es){
			ExStyle = es;
			return *this;
		}
		WINDOW& WINDOW::WindowStyle(const DWORD s){
			WStyle = s;
			return *this;
		}
		WINDOW& WINDOW::WindowTitle(const std::string title){
			WTitle = title;
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
		std::string WINDOW::GetTitleName(){
			return WTitle;
		}
		void WINDOW::ResizeClient(){
			RECT wrect, crect;
			GetWindowRect(hwnd, &wrect);
			GetClientRect(hwnd, &crect);
			
			int _Width = (wrect.right - wrect.left) - (crect.right - crect.left) + GetSize()[0];
			int _Height = (wrect.bottom - wrect.top) - (crect.bottom - crect.top) + GetSize()[1];
			
			SetWindowPos(hwnd, NULL, 0, 0, _Width, _Height, SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOMOVE);
		}
		void WINDOW::Create(){
			
			hwnd = CreateWindowEx(
				ExStyle,
				GetClassName().c_str(), WTitle.c_str(),
				WStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				hparent, Menu, hinst, this);
			PROCMAP::Get_Instance().Register(hwnd, this);
			if(hwnd == nullptr){
				DEBUG::error_dialog(NULL);
			}
			ResizeClient();
			if(ChildWindow.size() != 0){
				for(auto v : ChildWindow){
					v->SetParentHandle(hwnd);
					v->Create();
					v->ESetProc();
				}
			}
		}
		void WINDOW::Create(const std::string title){
			WTitle = title;
			hwnd = CreateWindowEx(
				ExStyle,
				GetClassName().c_str(), WTitle.c_str(),
				WStyle,
				GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
				hparent, NULL, hinst, this);
			PROCMAP::Get_Instance().Register(hwnd, this);
			if(hwnd == nullptr){
				DEBUG::error_dialog(NULL);
			}
			ResizeClient();
			if(ChildWindow.size() != 0){
				for(auto v : ChildWindow){
					v->SetParentHandle(hwnd);
					v->Create();
					v->ESetProc();
					
				}
			}
		}
		
		void WINDOW::Child(WINDOW& ch, const HMENU Id){
			ch.SetMenu(Id);
			ChildWindow.push_back(&ch);
		}
		void WINDOW::SetMenu(const HMENU Id){
			Menu = Id;
		}
		
		HWND WINDOW::GetHandle(){
			return hwnd;
		}
		void WINDOW::SetHandle(HWND handle){
			hwnd = handle;
		}
		void WINDOW::SetParentHandle(HWND handle){
			hparent = handle;
		}
		
		
		LRESULT WINDOW::WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
			PAINTSTRUCT ps;
			HDC hdc;
			CODE code;
			
			switch(msg){
			case WM_COMMAND:
				if(ECOMMAND(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			case WM_CREATE:
				if(ECREATE(hwnd, msg, wp, lp))return EBack(hwnd, msg, wp, lp);
				else return 0;
				
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
				if(EMOUSE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
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
				if(EMDI(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//NC (throw down)
			case WM_NCDESTROY:
				if(ENCDESTROY(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			//NC HITTEST
			case WM_NCHITTEST:
				if(ENCHITTEST(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
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
				if(ENCMOUSE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
			//EDIT BOX or COMBO BOX (throw down)
			case WM_CLEAR:
			case WM_COPY:
			case WM_CUT:
			case WM_PASTE:
				if(EEDIT(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
			//CHAR CODE (throw down)
			case WM_CHAR:
			case WM_DEADCHAR:
			case WM_SYSCHAR:
			case WM_SYSDEADCHAR:
				if(ECHAR(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
			//KEY (throw down)
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				if(EKEY(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			case WM_CLOSE:
				if(ECLOSE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			case WM_DESTROY:
				if(EDESTROY(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			case WM_QUIT:
				if(EQUIT(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//SCROLL (throw down)
			case WM_HSCROLL:
			case WM_VSCROLL:
				if(ESCROLL(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//STATE (throw down)
			case WM_ENABLE:
			case WM_SHOWWINDOW:
				if(ESTATE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//FOCUS (throw down)
			case WM_KILLFOCUS:
			case WM_SETFOCUS:
				if(EFOCUS(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//MOVE
			case WM_MOVE:
				if(EMOVE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//SIZE
			case WM_SIZE:
				if(ESIZE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
			//TEXT (throw down)
			case WM_SETTEXT:
			case WM_GETTEXT:
			case WM_GETTEXTLENGTH:
				if(ENCMOUSE(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
			
			//MENU (throw down)
			case WM_INITMENU:
			case WM_INITMENUPOPUP:
			case WM_MENUCHAR:
			case WM_MENUSELECT:
				if(EMENU(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			//ITEM (throw down)
			case WM_MEASUREITEM:
			case WM_DRAWITEM:
				if(EITEM(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
			
			case WM_PAINT:
				if(EPAINT(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0L;
				
			case WM_NOTIFY:
				break;
			case WM_SETREDRAW:
				break;
				
			case WM_SYSCOLORCHANGE:
				break;
			case WM_SYSCOMMAND:
				break;
				
			case WM_TIMER:
				if(ETIMER(hwnd, msg, wp, lp)) return EBack(hwnd, msg, wp, lp);
				else return 0;
				
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
			if(RegisterFlag){
				DEBUG::DebugConsole::Get_Instance().Log("EntryProc was set");
			} else{
				std::cout << "HWND : " << hwnd << std::endl;
				DefProc = (WNDPROC)(LONG_PTR)GetWindowLong(hwnd, GWL_WNDPROC);
				SetWindowLong(hwnd, GWL_WNDPROC, (LONG)EntryProc);
			}
		}
		CODE WINDOW::ECREATE(const HWND, const UINT, const WPARAM, const LPARAM){return 1;}
		CODE WINDOW::EPAINT(const HWND, const UINT, const WPARAM, const LPARAM){return 1;}
		CODE WINDOW::ECLOSE(const HWND, const UINT, const WPARAM, const LPARAM){return 1;}
		CODE WINDOW::EDESTROY(const HWND, const UINT, const WPARAM, const LPARAM){
			PostQuitMessage(0);
			return 0;
		}
		CODE WINDOW::ECOMMAND(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EMOUSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EMDI(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ENCDESTROY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ENCHITTEST(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ENCMOUSE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EEDIT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ECHAR(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EKEY(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EQUIT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ESCROLL(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EACTIVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EFOCUS(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EMOVE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ESIZE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ETEXT(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EMENU(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::EITEM(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ETIMER(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		CODE WINDOW::ESTATE(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){return 1;}
		LRESULT CALLBACK WINDOW::EBack(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
			return CallWindowProc(DefProc, hwnd, msg, wp, lp);
		}
		void WINDOW::Show(int flag){
			ShowWindow(hwnd, flag);
			UpdateWindow(hwnd);
		}
		
		int WINDOW::Message(){
			while(GetMessage(&msg, NULL, 0, 0) > 0){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return (int)msg.wParam;
		}
		void WINDOW::Print(){
			DEBUG::DebugConsole::Get_Instance().Log("start create");
			DEBUG::DebugConsole::Get_Instance().Log(ExStyle);
			DEBUG::DebugConsole::Get_Instance().Log(GetClassName().c_str());
			DEBUG::DebugConsole::Get_Instance().Log(WTitle.c_str());
			DEBUG::DebugConsole::Get_Instance().Log(WStyle);
			DEBUG::DebugConsole::Get_Instance().Log(GetPos()[0]);
			DEBUG::DebugConsole::Get_Instance().Log(GetPos()[1]);
			DEBUG::DebugConsole::Get_Instance().Log(GetSize()[0]);
			DEBUG::DebugConsole::Get_Instance().Log(GetSize()[1]);
		}
	}
}