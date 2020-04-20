#include"azgu.hpp"


namespace AZ{
	namespace GUI{
		namespace WINDOW{
			static HINSTANCE hinstance = nullptr;
			static const int it_x = 0;
			static const int it_y = 1;
			static const int it_width = 0;
			static const int it_height = 1;
			
			void INIT(HINSTANCE h){
				hinstance = h;
			}
			
			POS::POS(){
				Pos[it_x] = 200;
				Pos[it_y] = 100;
			}
			POS::POS(int x, int y){
				Pos[it_x] = x;
				Pos[it_y] = y;
			}
			POS::~POS(){}
			int POS::X(){
				return Pos[it_x];
			}
			int POS::Y(){
				return Pos[it_y];
			}
			void POS::Set(int x, int y){
				Pos[it_x] = x;
				Pos[it_y] = y;
			}
			std::array<int, 2> POS::Get(){
				return Pos;
			}
			SIZE::SIZE(){
				Size[it_width] = 300;
				Size[it_height] = 200;
			}
			SIZE::SIZE(int w, int h){
				Size[it_width] = w;
				Size[it_height] = h;
			}
			SIZE::~SIZE(){}
			int SIZE::Width(){
				return Size[it_width];
			}
			int SIZE::Height(){
				return Size[it_height];
			}
			void SIZE::Set(int w, int h){
				Size[it_width] = w;
				Size[it_height] = h;
			}
			std::array<int, 2> SIZE::Get(){
				return Size;
			}
			
			STATE::STATE(){
				size = SIZE(300, 200);
				pos = POS(CW_USEDEFAULT, CW_USEDEFAULT);
			}
			STATE::STATE(int width, int height){
				size = SIZE(width, height);
				pos = POS(CW_USEDEFAULT, CW_USEDEFAULT);
			}
			STATE::~STATE(){}
			void STATE::SetSize(int width, int height){
				size.Set(width, height);
			}
			void STATE::SetPos(int x, int y){
				pos.Set(x, y);
			}
			std::array<int, 2> STATE::GetSize(){
				return size.Get();
			}
			std::array<int, 2> STATE::GetPos(){
				return pos.Get();
			}
			
			AZWINDOW::AZWINDOW() : STATE(), wcl(hinstance){
				title = "Azalea Window";
				
			}
			AZWINDOW::AZWINDOW(int w, int h) : STATE(w, h), wcl(hinstance){
				title = "Azalea Window";
			}
			AZWINDOW::AZWINDOW(int w, int h, std::string Title) : STATE(), wcl(hinstance){
				title = Title;
			}
			AZWINDOW::AZWINDOW(std::string Title) : STATE(), wcl(hinstance){
				title = Title;
			}
			AZWINDOW::~AZWINDOW(){}
			void AZWINDOW::Create(){
				hwnd = CreateWindowEx(WS_EX_ACCEPTFILES | WS_EX_OVERLAPPEDWINDOW ,
					wcl.GetClassName().c_str() , title.c_str() ,
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					GetPos()[0], GetPos()[1], GetSize()[0], GetSize()[1],
					NULL , NULL , hinstance, &wcl);
				if(hwnd == nullptr){
					DEBUG::error_dialog(NULL);
				}
			}
			void AZWINDOW::Create(std::string Title){
				title = Title;
				hwnd = CreateWindowEx(
					WS_EX_ACCEPTFILES | WS_EX_OVERLAPPEDWINDOW,
					wcl.GetClassName().c_str(), title.c_str(),
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					GetPos()[0], GetPos()[1],
					GetSize()[0], GetSize()[1], NULL, NULL, hinst, &wcl);
				if(hwnd == nullptr){
					DEBUG::error_dialog(NULL);
				}
			}
			AZWCL* AZWINDOW::SetClass(){
				return &wcl;
			}
			
			HWND AZWINDOW::GetHandle(){
				return hwnd;
			}
			
			void AZWINDOW::Show(int flag){
				ShowWindow(hwnd, flag);
				UpdateWindow(hwnd);
			}
			void AZWINDOW::UseDebug(bool flag){
				wcl.UseDebug(flag);
			}
			
			int AZWINDOW::Message(){
				while(GetMessage(&msg, NULL, 0, 0) > 0){
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				return (int)msg.wParam;
			}
		}
	}
}