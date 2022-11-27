#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include<windows.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<list>
#include<string>

#include"../UTIL/utility.hpp"

#define CVTMSGWC(x) case x: return std::wstring(L ## #x L" : ") + std::to_wstring(x)

//typedef AZ::GUI::CODE (*EVENTFUNCP)(HWND, UINT, WPARAM, LPARAM);

#define EV_LUP 0x3000
#define EV_MUP 0x3001
#define EV_RUP 0x3002
#define EV_LCLICK 0x3003
#define EV_MCLICK 0x3004
#define EV_RCLICK 0x3005
#define EV_LDCLICK 0x3006
#define EV_MDCLICK 0x3007
#define EV_RDCLICK 0x3008

#define EV_NCLUP 0x3010
#define EV_NCMUP 0x3011
#define EV_NCRUP 0x3012
#define EV_NCLCLICK 0x3013
#define EV_NCMCLICK 0x3014
#define EV_NCRCLICK 0x3015
#define EV_NCLDCLICK 0x3016
#define EV_NCMDCLICK 0x3017
#define EV_NCRDCLICK 0x3018


namespace AZ{
	namespace GUI{
		using CODE = int;
		
		std::wstring CvtMsgCodetowc(UINT);
		
		typedef class _EVENT EVENT;
		class EVENT_BASE;
		
		class EVCMD : public UTIL::Singleton<EVCMD>{
			
		};
		class _EVENT : public UTIL::Singleton<EVENT>{
			using EVENTFUNCP = AZ::GUI::CODE (*)(HWND, UINT, WPARAM, LPARAM);
			
			std::map<UINT, std::vector<EVENTFUNCP> > msg;
			std::map<EVENT_BASE*, std::wstring> RegList;
		public:
			_EVENT();
			~_EVENT();
			
			void Register(UINT, EVENTFUNCP);
			void Register(EVENT_BASE*, std::wstring);
			
			bool UnRegister(UINT, EVENTFUNCP);
			bool UnRegister(EVENT_BASE*);
			
			std::vector<AZ::GUI::CODE> Do(HWND, UINT, WPARAM, LPARAM);
			std::list< std::wstring > GetRegList();
		};
		
		class EVENT_BASE{
			
		public:
			EVENT_BASE();
			~EVENT_BASE();
			
			virtual Register() = 0;
			virtual UnRegister() = 0;
		};
	}
}

#endif