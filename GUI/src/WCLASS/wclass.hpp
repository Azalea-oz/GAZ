#ifndef __WINDOWCLASS_HPP__
#define __WINDOWCLASS_HPP__

#include<windows.h>
#include<array>
#include<map>
#include<iostream>

#include"../UTIL/utility.hpp"



namespace AZ{
	namespace GUI{
		
		class STATE{
			UTIL::POINT2<int> Size;
			UTIL::POINT2<int> Pos;
			
			HWND hwnd;
			
		public:
			STATE();
			STATE(const int, const int);
			STATE(const int, const int, const int, const int);
			STATE(UTIL::POINT2<int>);
			STATE(UTIL::POINT2<int>, UTIL::POINT2<int>);
			~STATE();
			
			void SetSize(const int, const int);
			void SetSize(UTIL::POINT2<int>);
			std::array<int, 2> GetSize();
			
			void SetPos(const int, const int);
			void SetPos(UTIL::POINT2<int>);
			std::array<int, 2> GetPos();
			
			void SetHandle(HWND);
			HWND GetHandle();
		};
		
		struct MOUSE{
			WPARAM wp;
			LPARAM lp;
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