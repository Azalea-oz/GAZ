#ifndef _PAINT_HPP_
#define _PAINT_HPP_ 0x0001

#include<windows.h>
#include<gdiplus.h>
#include<string>
#include<vector>
#include"../defines.hpp"
#include"../WCLASS/wclass.hpp"
#include"../SINGLETON/singleton.hpp"

namespace AZ{
	namespace GUI{
		namespace PAINT{
			
			typedef struct RGB32{
				BYTE B;
				BYTE G;
				BYTE R;
				BYTE A;
				
				RGB32();
				bool isBlack();
				bool isWhite();
				bool isBlue();
				bool isGreen();
				bool isRed();
				bool isInvisible();
			} RGB32;
			
			/*gdi initializer*/
			/*singleton*/
			class InitGdiplus : protected SINGLETON::Singleton<InitGdiplus>{
				ULONG_PTR gdiplusToken;
			public:
				InitGdiplus();
				~InitGdiplus();
				
			};
			
			//converter class
			template<typename T>
			class Converter{
				HWND hwnd;
			public:
				Converter();
				~Converter();
				
				HRGN Region(HBITMAP);
				
				template<typename Func, typename DATA>
				LPVOID UserCustom(Func, DATA);
			};
			
			class IMAGE : protected STATE{
				tstring FileName;
			public:
				IMAGE(const wchar_t *filename, int w, int h, int x, int y);
				IMAGE(const wchar_t *filename, STATE state);
				IMAGE(const wchar_t *filename, POINT2 size, POINT2 pos);
				IMAGE();
				~IMAGE();
				
				void Paint(HDC, int, int, int, int);
				
				Converter<IMAGE> Convert;
				
			};
			
			
			class IMAGES : private InitGdiplus{
				std::vector<IMAGE> imgs;
			public:
				IMAGES();
				~IMAGES();
				
				//paint images
				void Paint(HDC, int, int, int, int);
				
				Converter<IMAGES> Convert;
				
			};
			
			
		}
	}
}

#endif