#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include<windows.h>
#include<ios>
#include<iomanip>
#include<iostream>
#include<sstream>
#include<cstdio>
#include<ctime>
#include<chrono>
#include<io.h>
#include<fcntl.h>

#include"dos_color.hpp"
#include"../SINGLETON/singleton.hpp"

#define DLL_EXPORT  __attribute__((visibility ("default")))

/*
class HOOKER{
	HHOOK hhk;
	static HOOKER *tmp;
public:
	HOOKER();
	~HOOKER();
	Start();
	End();
	
private:
	static LRESULT CALLBACK EntryProc(int, WPARAM, LPARAM);
public:
	virtual LRESULT HookProc(int, WPARAM, LPARAM);
};
*/

namespace DEBUG{
	void error_dialog(HWND);
	BOOL WINAPI HandlerRoutine(DWORD);
	template<typename T>
	constexpr void DLog(T);
	
	class DebugConsole : public SINGLETON::Singleton<DebugConsole>{
		HANDLE hout;
		int hConsole;
		bool DEBUG_TIME;
		int Debug_Line;
		bool UseFlag;
		
		FILE *fpOut;
		FILE *fpIn;
		
		DWORD NumOfWritten;
		
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