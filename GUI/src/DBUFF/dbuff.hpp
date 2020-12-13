#ifndef __DBUFF_HPP__
#define __DBUFF_HPP__


namespace AZ{
	namespace GUI{
		namespace WINDOW{
			class DBUFF{
				HBITMAP hBitMap;
				HDC hMemDC;
				
			public:
				DBUFF(HWND);
				~DBUFF();
				
				
			};
		}
	}
}

#endif