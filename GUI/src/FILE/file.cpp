#include"file.hpp"
#define DDFILEMSG 30000

namespace AZ{
	namespace SYSTEM{
		namespace FILE{
			
			
			SFILE::SFILE(GUI::WINDOW *wnd){
				wnd->RegMsgCode(DDFILE, DDFILEMSG);
				
			}
			SFILE::~SFILE(){}
			
			CODE DDFILE(const HWND, const UINT, const WPARAM, const LPARAM){
				MessageBoxW(NULL, L"DDFILE TEST", L"test", MB_OK);
			}
			
		}
	}
}