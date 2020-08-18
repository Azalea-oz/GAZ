#include"err.hpp"

namespace AZ{
	namespace GUI{
		namespace ERR{
			void Dialog(HWND hwnd){
				DWORD ErrorCode = GetLastError();
				LPVOID lpMsgBuf;
				
				FormatMessage(
					FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),//   言語を指定
					(LPTSTR)&lpMsgBuf, 0, NULL);
				
				MessageBox(hwnd, (LPCTSTR)lpMsgBuf, _TEXT("Error"), MB_OK | MB_ICONINFORMATION);
				
				LocalFree(lpMsgBuf);
			}
			
			void Print(){
				DWORD ErrorCode = GetLastError();
				LPVOID lpMsgBuf;
				
				FormatMessage(
					FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),//   言語を指定
					(LPTSTR)&lpMsgBuf, 0, NULL);
				
				std::string ErrStr = (char*)lpMsgBuf;
				std::cerr << ErrStr << std::endl;
			}
		}
	}
}