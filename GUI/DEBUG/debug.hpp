#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include<windows.h>
#include<ios>
#include<iomanip>
#include<iostream>
#include<cstdio>
#include<ctime>
#include<chrono>
#include<string>

#include"dos_color.hpp"
#include"../SINGLETON/singleton.hpp"

#define DLL_EXPORT  __attribute__((visibility ("default")))

namespace DEBUG{
	void error_dialog(HWND);
	BOOL WINAPI HandlerRoutine(DWORD);
	template<typename T>
	constexpr void DLog(T);
	
	class DebugConsole : public SINGLETON::Singleton<DebugConsole>{
		HANDLE hout;
		bool DEBUG_TIME;
		int Debug_Line;
		bool UseFlag;
		void DebugLogLine();
	public:
		DebugConsole();
		~DebugConsole();
		void SetAttr(WORD);
		void UseTime();
		void UseDebug(bool);
		void Init();
		
		template<typename T>
		void Log(T x);
		
		
		template<typename T>
		void CmdLog(T cmd, T msg);
	};
	
	
	
	
}


namespace Time{
	void NowTime();
}

#endif