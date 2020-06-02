#pragma once

#include<windows.h>
#include<array>
#include<map>

namespace AZ{
	namespace GUI{
		
		class POINT2{
			std::array<int, 2> point;
		
		public:
			POINT2();
			POINT2(const int, const int);
			~POINT2();
			
			std::array<int, 2> Get();
			void Set(const int, const int);
		};
		
		class STATE{
			POINT2 Size;
			POINT2 Pos;
			
			HWND hwnd;
			
		public:
			STATE();
			STATE(const int, const int);
			~STATE();
			
			void SetSize(const int, const int);
			std::array<int, 2> GetSize();
			
			void SetPos(const int, const int);
			std::array<int, 2> GetPos();
			
			void SetHandle(HWND);
			HWND GetHandle();
		};
		
		enum class EVENT_CODE : int{
			COMMAND = 0,
			CREATE = 1,
			PAINT = 2,
			CLOSE = 3,
			DESTROY = 4,
			MOUSE = 5,
			MDI = 6,
			NCDESTROY = 7,
			NCHITTEST = 8,
			NCMOUSE = 9,
			EDIT = 10,
			CHAR = 11,
			KEY = 12,
			QUIT = 13,
			SCROLL = 14,
			ACTIVE = 15,
			FOCUS = 16,
			MOVE = 17,
			SIZE = 18,
			TEXT = 19,
			MENU = 20,
			ITEM = 21,
			TIMER = 22,
			STATE = 23,
		};
		
		
	}
}

#endif