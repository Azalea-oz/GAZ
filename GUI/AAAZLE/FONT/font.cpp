#include"font.hpp"

namespace AZ{
	namespace GUI{
		namespace FONTS{
			
			FONT::FONT(){
				Height = Width = 0;
				Escapement = Orientation = 0;
				Weight = FW_REGULAR;
				Italic = Under = StrikeOut = false;
				
				
				
			}
			FONT::~FONT(){}
			
			HFONT FONT::Create(){}
		}
	}
}