#include"paint.hpp"

namespace AZ{
	namespace GUI{
		namespace PAINT{
			
			RGB32::RGB32() : B(0), G(0), R(0), A(0){};
			bool RGB32::isBlack(){
				if(B == 0x00 && G == 0x00 && R == 0x00) return true;
				return false;
			}
			bool RGB32::isWhite(){
				if(B == 0xFF && G == 0xFF && R == 0xFF) return true;
				return false;
			}
			bool RGB32::isBlue(){
				if(B == 0xFF && G == 0x00 && R == 0x00) return true;
				return false;
			}
			bool RGB32::isGreen(){
				if(B == 0x00 && G == 0xFF && R == 0x00) return true;
				return false;
			}
			bool RGB32::isRed(){
				if(B == 0x00 && G == 0x00 && R == 0xFF) return true;
				return false;
			}
			bool RGB32::isInvisible(){
				if(A == 0xFF) return true;
				return false;
			}
			
			/*gdi initializer*/
			/*singleton*/
			InitGdiplus::InitGdiplus(){
				Gdiplus::GdiplusStartupInput gdiplusStartupInput;
				Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			}
			InitGdiplus::~InitGdiplus(){
				Gdiplus::GdiplusShutdown(gdiplusToken);
			}
			
			
			template<typename T>
			Converter<T>::Converter(){};
			
			template<typename T>
			Converter<T>::~Converter(){};
			
			template<typename T>
			HRGN Converter<T>::Region(HBITMAP hBMP){
				BITMAP bi;
				GetObject(hBMP, sizeof(BITMAP), &bi);
				HRGN hRgn = CreateRectRgn(0, 0, bi.bmWidth, bi.bmHeight);

				// コンパチブルDCに一度描画してから点を検査
				HDC hDC = GetDC(hwnd);
				HDC memDC = CreateCompatibleDC(hDC);
				SelectObject(memDC, hBMP);
				int x, y;
				for(y=0; y<bi.bmHeight; y++){
					for(x=0; x<bi.bmWidth; x++){
						// ラインを走査して0x00000000以外はリージョン範囲からはずす
						COLORREF color = GetPixel(memDC, x, y);
						if(color != 0x00000000){
							HRGN SubRgn = CreateRectRgn(x, y, x+1, y+1);
							CombineRgn(hRgn, hRgn, SubRgn, RGN_DIFF);
							DeleteObject(SubRgn);
						}
					}
				}
				DeleteDC(memDC);
				ReleaseDC(hwnd, hDC);

				return hRgn;
			};
			
			
			template<typename T>
			template<typename Func, typename DATA>
			LPVOID Converter<T>::UserCustom(Func func, DATA ImgData){
				return func(ImgData);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			/*
			void IMGPAINT::PaintImage(HDC hdc, WCHAR *filename, int x, int y, int w, int h){
				Gdiplus::Graphics grap(hdc);
				Gdiplus::Image image(filename);
				
				grap.DrawImage(&image, x, y, w, h);
			}
			
			
			IMAGE::IMAGE(const wchar_t *filename, int w, int h, int x, int y){
				SetSize(w, h);
				SetPos(x, y);
				FileName_w = filename;
			}
			
			IMAGE::IMAGE(const wchar_t *filename, STATE state) : STATE(state){
				FileName_w = filename;
			}
			IMAGE::IMAGE(const wchar_t *filename, POINT2 size, POINT2 pos){
				SetSize(size);
				SetPos(pos);
				FileName_w = filename;
			}
			
			IMAGE::IMAGE(){}
			IMAGE::~IMAGE(){}
			*/
		}
	}
}