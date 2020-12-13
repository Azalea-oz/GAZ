#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include<windows.h>
#include<string>

#define CVTMSGWC(x) case x: return L ## #x

namespace AZ{
	namespace GUI{
		using CODE = int;
		
		std::wstring CvtMsgCodetowc(UINT);
	}
}

#endif