#ifndef _PAINT_HPP_
#define _PAINT_HPP_

#include<gdiplus.h>
#include"../SINGLETON/singleton.hpp"

namespace AZ{
	namespace GUI{
		namespace PAINT{
			
			class AZPEN{
				HPEN hPen;
				HPEN hOldPen;
			};
			
			/*gdi initializer*/
			/*singleton*/
			class IMGPAINT : public SINGLETON::Singleton<IMGPAINT>{
				ULONG_PTR gdiplusToken;
				
			public:
				IMGPAINT();
				~IMGPAINT();
				void PaintImage(HDC, WCHAR*, int, int, int, int);
			};
		}
	}
}

#endif