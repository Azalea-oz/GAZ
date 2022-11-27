#include"../../AAAZLE.hpp"

namespace AZ{
	namespace GUI{
		namespace COMPO{
			
			
			
			constexpr bool NORMAL = false;
			constexpr bool AUTO = true;
			
			template<DWORD BTNSTYLE = BS_PUSHBUTTON>
			class BTN : public AZ::GUI::WINDOW{
				UINT ButtonMessage;
				std::function<void(PVOID)> ClickFunc;
				
			public:
				BTN(int x, int y, std::string s, UINT msg) : WINDOW(x, y, s){
					WClassName(L"Button");
					SetWindowStyle(WS_CHILD | WS_VISIBLE | BTNSTYLE);
				}
				BTN(int x, int y, std::wstring s, UINT msg) : WINDOW(x, y, s){
					WClassName(L"Button");
					SetWindowStyle(WS_CHILD | WS_VISIBLE | BTNSTYLE);
				}
				BTN(UINT msg) : WINDOW(){
					WClassName(L"Button");
					SetWindowStyle(WS_CHILD | WS_VISIBLE | BTNSTYLE);
				}
				~BTN(){}
				
				void setType(bool f, bool na){
					if(f){
						if(na) _WindowStyle |= BS_3STATE;
						else _WindowStyle |= BS_AUTO3STATE;
					} else{
						if(na) _WindowStyle &= ~BS_3STATE;
						else _WindowStyle &= ~BS_AUTO3STATE;
					}
				}
				
				void BTN::OnClick(std::function<void(PVOID)> _ClickFunc){
					ClickFunc = _ClickFunc;
				}
				
			private:
				AZ::GUI::CODE CHILDMSG(const HWND hwnd, const UINT msg, const WPARAM wp, const LPARAM lp){
					switch(LOWORD(wp) == ButtonMessage){
					case true:
						ClickFunc((PVOID)&Args);
					}
				}
			public:
				
			};
			
			namespace SAMPLE{
				class N3STATE : BTN{};
				class A3STATE : BTN{};
				
				class NCHECK : BTN{};
				class ACHECK : BTN{};
				
				class NRADIO : BTN{};
				class ARADIO : BTN{};
				
				class TOPBTN : BTN{};
				class CENTERBTN : BTN{};
				class BOTTOMBTN : BTN{};
				
				class NCOMMANDLINK : BTN{};
				class DEFCOMMANDLINK : BTN{};
				
				class DEFPUSH : BTN{};
				class NPUSH : BTN{};
				
				class DEFSPLIT : BTN{};
				class NSPLIT : BTN{};
				
				class GROUP : BTN{};
				
			}
		}
	}
}