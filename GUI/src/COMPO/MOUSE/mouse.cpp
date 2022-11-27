#include"../../AAAZLE.hpp"
#include"../compo.hpp"


namespace AZ{
	namespace GUI{
		namespace COMPO{
			
			
			class MOUSE :
				private AZ::GUI::COMPO::BASE,
				public AZ::UTIL::SINGLETON<MOUSE>{
				
			public:
				MOUSE(){}
				~MOUSE(){}
			};
			
		}
	}
}