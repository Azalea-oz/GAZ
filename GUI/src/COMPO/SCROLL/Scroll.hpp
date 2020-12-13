#include"../AAAZLE.hpp"


namespace AZ{
	namespace GUI{
		namespace COMPO{
			class SCRLL : public WINDOW{
				SCROLLINFO scr;
				
				SCRLL();
				SCRLL(int _size, int _page);
				~SCRLL();
				
				
			};
		};
	};
};