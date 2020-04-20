#include"../azgu.hpp"


namespace AZ{
	namespace GUI{
		namespace WINDOW{
			using AZWCLP = AZWCL*;
			AZWCL* AZWCL::tmp;
			
			/*constructor*/
			AZWCL::AZWCL(HINSTANCE hinst){
				Debug = nullptr;
				tmp = this;
				cbSize = sizeof(WNDCLASSEX);
				style = CS_HREDRAW | CS_VREDRAW;
				lpfnWndProc = entryProc;
				cbClsExtra = 0;
				cbWndExtra = 0;
				hInstance = hinst;
				hIcon = LoadIcon(NULL , IDI_APPLICATION);
				hIconSm = LoadIcon(NULL , IDI_APPLICATION);
				hCursor = LoadCursor(NULL, IDC_ARROW);
				hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
				lpszMenuName = "AzMenu";
				lpszClassName = "AzWindow";
				
				
			}
			/*destructor*/
			AZWCL::~AZWCL(){
				if(Debug != nullptr){
					delete Debug;
				}
			}
			/*init AZWCL*/
			void AZWCL::Init(HINSTANCE hinst){
				cbSize = sizeof(WNDCLASSEX);
				style = CS_HREDRAW | CS_VREDRAW;
				lpfnWndProc = entryProc;
				cbClsExtra = 0;
				cbWndExtra = 0;
				hInstance = hinst;
				hIcon = LoadIcon(NULL , IDI_APPLICATION);
				hIconSm = LoadIcon(NULL , IDI_APPLICATION);
				hCursor = LoadCursor(NULL, IDC_ARROW);
				hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
				lpszMenuName = "AzMenu";
				lpszClassName = "AzWindow";
			}
			/*Get instance*/
			AZWCL *AZWCL::GetInst(){
				return this;
			}
			/*Set Class param*/
			AZWCL *AZWCL::SetClass(){
				return GetInst();
			}
			/*set */
			AZWCL* AZWCL::Size(UINT wcex_cbSize){
				cbSize = wcex_cbSize;
				return this;
			}
			AZWCL *AZWCL::Style(UINT wcex_style){
				style = wcex_style;
				return this;
			}
			AZWCL *AZWCL::WndProc(WNDPROC wcex_lpfnWndProc){
				lpfnWndProc = wcex_lpfnWndProc;
				return this;
			}
			AZWCL *AZWCL::ClsExtra(int wcex_cbClsExtra){
				cbClsExtra = wcex_cbClsExtra;
				return this;
			}
			AZWCL *AZWCL::WndExtra(int wcex_cbWndExtra){
				cbWndExtra = wcex_cbWndExtra;
				return this;
			}
			AZWCL *AZWCL::Instance(HINSTANCE wcex_hInstance){
				hInstance = wcex_hInstance;
				return this;
			}
			AZWCL *AZWCL::Icon(HICON wcex_hIcon){
				hIcon = wcex_hIcon;
				return this;
			}
			AZWCL *AZWCL::IconSm(HICON wcex_hIconSm){
				hIconSm = wcex_hIconSm;
				return this;
			}
			AZWCL *AZWCL::Cursor(HCURSOR wcex_hCursor){
				hCursor = wcex_hCursor;
				return this;
			}
			AZWCL *AZWCL::Background(HBRUSH wcex_hbrBackground){
				hbrBackground = wcex_hbrBackground;
				return this;
			}
			AZWCL *AZWCL::MenuName(std::string wcex_lpszMenuName){
				lpszMenuName = wcex_lpszMenuName;
				return this;
			}
			AZWCL *AZWCL::ClassName(std::string wcex_lpszClassName){
				lpszClassName = wcex_lpszClassName;
				return this;
			}
			
			std::string AZWCL::GetClassName(){
				return lpszClassName;
			}

			AZWCL *AZWCL::Register(){
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
					return nullptr;
				}
				return this;
			}
			
			const WNDCLASSEX AZWCL::GetWcex(){
				return wcex;
			}
			
			void AZWCL::Print(){
				Debug->Log(cbSize);
				Debug->Log(style);
				Debug->Log(lpfnWndProc);
				Debug->Log(cbClsExtra);
				Debug->Log(cbWndExtra);
				//hInstance;
				Debug->Log(hIcon);
				Debug->Log(hIconSm);
				Debug->Log(hCursor);
				Debug->Log(hbrBackground);
				Debug->Log(lpszMenuName);
				Debug->Log(lpszClassName);
				Debug->Log("");
				Debug->Log("");
			}
			
			void AZWCL::Print(const WNDCLASSEX wcex){
				Debug->Log(wcex.cbSize);
				Debug->Log(wcex.style);
				Debug->Log(wcex.lpfnWndProc);
				Debug->Log(wcex.cbClsExtra);
				Debug->Log(wcex.cbWndExtra);
				//hInstance;
				Debug->Log(wcex.hIcon);
				Debug->Log(wcex.hIconSm);
				Debug->Log(wcex.hCursor);
				Debug->Log(wcex.hbrBackground);
				Debug->Log(wcex.lpszMenuName);
				Debug->Log(wcex.lpszClassName);
				Debug->Log("");
				Debug->Log("");
			}
			void AZWCL::UseDebug(bool use){
				if(use){
					if(Debug != nullptr){
						return;
					}
					Debug = new DEBUG::DebugConsole();
				}else{
					delete Debug;
				}
			}
			LRESULT AZWCL::AZPROC(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
				switch (msg) {
				case WM_CREATE:
					CreateWindowEx(0, "BUTTON", "ボタン", WS_CHILD | WS_VISIBLE, 30, 30, 80, 40, hwnd, (HMENU)ID_BUTTON, ((LPCREATESTRUCT)lp)->hInstance, NULL);
					
					return 0;
				case WM_COMMAND:
					switch (LOWORD(wp)) {
					case ID_BUTTON:
						MessageBox(NULL, "押したね", "メッセージボックス", MB_OK);
						return 0;
					case IDM_END:
						MessageBox(NULL, "押したね", "メッセージボックス", MB_OK);
						SendMessage(hwnd, WM_CLOSE, 0, 0);
						return 0;
					case IDM_ON:
						return 0;
					case IDM_OFF:
						return 0;
					}
					break;
				case WM_CLOSE:
					if (IDYES == MessageBox(hwnd, "しゅ～りょ～？", "Confirmation", MB_YESNO)) {
						DestroyWindow(hwnd);
					}
					return 0;
				case WM_DESTROY:
					PostQuitMessage(0);
					return 0;
				}
				
				return DefWindowProc(hwnd, msg, wp, lp);
			}
			LRESULT CALLBACK AZWCL::entryProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
				AZWCL *ptr = (AZWCL*)(LONG_PTR)GetWindowLong(hwnd, GWLP_USERDATA);
				
				if(ptr != nullptr){
					return ptr->AZPROC(hwnd, msg, wp, lp);
				} else{
					if(msg == WM_CREATE || msg == WM_INITDIALOG){
						ptr = (AZWCL*)(((LPCREATESTRUCT)lp)->lpCreateParams);
						SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)(tmp));
						SendMessage(hwnd, msg, wp, lp);
						
						tmp = nullptr;
					}
				}
				return DefWindowProc(hwnd, msg, wp, lp);
			}
		}
	}
}