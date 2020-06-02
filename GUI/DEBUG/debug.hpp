#pragma once

#include<windows.h>
#include<ios>
#include<iomanip>
#include<iostream>
#include<cstdio>
#include<ctime>
#include<chrono>

#include"dos_color.hpp"
#include"../SINGLETON/singleton.hpp"

#define DLL_EXPORT  __attribute__((visibility ("default")))

namespace DEBUG{
	DLL_EXPORT void error_dialog(HWND);
	DLL_EXPORT BOOL WINAPI HandlerRoutine(DWORD);
	template<typename T>
	constexpr void DLog(T);
	
	class DLL_EXPORT DebugConsole : public SINGLETON::Singleton<DebugConsole>{
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