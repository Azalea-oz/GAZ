#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include<windows.h>
#include<string>

#define CVTMSGWC(x) case x: return L ## #x

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
	}
}

#endif