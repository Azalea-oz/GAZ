#include"utility.hpp"


namespace AZ{
	namespace UTIL{
		static unsigned int SCREEN_WIDTH = 0;
		static unsigned int SCREEN_HEIGHT = 1;
		
		
		// 画面サイズの取得
		// bool wh 縦と横の指定
		//      true 縦
		//      false 横
		int GetDesktopSize(bool wh){
			//画面サイズの格納先
			RECT rc;
			
			//画面サイズの取得
			#if AZ_STR_ENCODE == STR_ENCODE_SJIS
			SystemParametersInfoA(SPI_GETWORKAREA, 0, &rc, sizeof(rc));
			#elif AZ_STR_ENCODE == STR_ENCODE_UNICODE
			SystemParametersInfoW(SPI_GETWORKAREA, 0, &rc, sizeof(rc));
			#endif
			
			switch(wh){
			case true:
				return rc.bottom - rc.top;
			case false:
				return rc.right - rc.left;
			}
		}
		
		std::wstring StoWS(std::string str){
			int BufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
			
			wchar_t *Buffer = new wchar_t[BufferSize];
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, Buffer, BufferSize);
			
			std::wstring wstr(Buffer, Buffer + BufferSize - 1);
			
			delete[] Buffer;
			return wstr;
		}
		
		std::string WStoS(std::wstring wstr){
			int BufferSize = WideCharToMultiByte(CP_OEMCP, 0, wstr.c_str(), -1, (char*)NULL, 0, NULL, NULL);
			
			char *Buffer = new char[BufferSize];
			WideCharToMultiByte(CP_OEMCP, 0, wstr.c_str(), -1, Buffer, BufferSize, NULL, NULL);
			
			std::string str(Buffer, Buffer + BufferSize - 1);
			
			delete[] Buffer;
			return str;
		}
		
		template<class T>
		TREE<T> TREE<T>::Right(){
			return *right;
		}
		
		template<class T>
		TREE<T> TREE<T>::Left(){
			return *left;
		}
		
		template<class T>
		void  TREE<T>::Insert(T &d){
			data = d;
		}
		
		NoMultiWindow::NoMultiWindow(){
		}
		NoMultiWindow::~NoMultiWindow(){}
	}
}