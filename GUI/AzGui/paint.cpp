#include"paint.hpp"

namespace AZ{
	namespace GUI{
		namespace PAINT{
			/*gdi initializer*/
			/*singleton*/
			IMGPAINT::IMGPAINT(){
					Gdiplus::GdiplusStartupInput gdiplusStartupInput;
					Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			}
			IMGPAINT::~IMGPAINT(){
				Gdiplus::GdiplusShutdown(gdiplusToken);
			}
			void IMGPAINT::PaintImage(HDC hdc, WCHAR *filename, int x, int y, int w, int h){
				Gdiplus::Graphics grap(hdc);
				Gdiplus::Image image(filename);
				
				grap.DrawImage(&image, x, y, w, h);
			}
		}
	}
}