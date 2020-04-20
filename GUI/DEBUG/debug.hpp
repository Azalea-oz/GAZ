#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include<windows.h>
#include<ios>
#include<iomanip>
#include<iostream>
#include<cstdio>
#include"dos_color.hpp"
#include"../Time/AzTime.hpp"
#include"../SINGLETON/singleton.hpp"

namespace DEBUG{
	void error_dialog(HWND);
	BOOL WINAPI HandlerRoutine(DWORD);
	template<typename T>
	constexpr void DLog(T);
	
	
	
	
	void DebugLogLine();
	
	class DebugConsole : public SINGLETON::Singleton<DebugConsole>{
		HMENU menu;
		HANDLE hout;
		bool DEBUG_TIME;
		int Debug_Line;
		
		void DebugLogLine();
	public:
		DebugConsole();
		~DebugConsole();
		void SetAttr(WORD);
		void UseTime();
		
		template<typename T>
		void Log(T x);
		
		template<typename T>
		void CmdLog(T cmd, T msg);
	};
	
	
	
	
}

#endif