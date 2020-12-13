#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include<windows.h>
#include<string>
#include<vector>
#include"../SINGLETON/singleton.hpp"

namespace AZ{
	namespace GUI{
		namespace CLK{
			class CLOCK : protected SINGLETON::Singleton<CLOCK>{
				
			public:
				CLOCK();
				~CLOCK();
				
				GetTime();
				Setfps();
				
			};
			
		}
	}
}

#endif