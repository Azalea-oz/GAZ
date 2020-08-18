#pragma once

#include<windows.h>
#include<string>
#include<vector>
#include"../WCLASS/wclass.hpp"
#include"../SINGLETON/singleton.hpp"

namespace AZ{
	namespace GUI{
		namespace MEMORY{
			
			
			class FRAGMENT : public STATE{
				
			public:
				FRAGMENT();
				~FRAGMENT();
			};
			
			
			class MEM : public STATE{
				FRAGMENT Frag;
				
				
				
			public:
				MEM();
				~MEM();
				
				
			};
			
			
			
		}
	}
}

#endif