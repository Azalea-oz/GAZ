#ifndef _FONT_HPP_
#define _FONT_HPP_ 0x0001

#include<windows.h>
#include<gdiplus.h>
#include<string>
#include<vector>
#include"../defines.hpp"

namespace AZ{
	namespace GUI{
		namespace FONTS{
			
			class FONT{
				int Height;
				int Width;
				int Weight;
				
				int Escapement;
				int Orientation;
				
				DWORD Italic;
				DWORD Under;
				DWORD StrikeOut;
				
				DWORD CharSet;
				DWORD OutputPrecision;
				DWORD ClipPrecision;
				DWORD Quality;
				DWORD PitchAndFamily;
				
				std::string FontName;
				std::wstring FontNameW;
				
			public:
				FONT();
				FONT(std::string);
				FONT(std::wstring);
				~FONT();
				
				HFONT Create();
				void TextColor();
				void BkColor();
				void Draw();
				
				
				
			};
		}
	}
}

#endif