#pragma once

#include<windows.h>
#include<ios>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<ctime>
#include<chrono>
#include<io.h>
#include<fcntl.h>
#include<vector>

#include"dos_color.hpp"
#include"../src/UTIL/utility.hpp"
#include"util.hpp"

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
	void error_dialog(HWND, std::string);
	void error_dialog(HWND, std::wstring);
	
	BOOL WINAPI HandlerRoutine(DWORD);
	template<typename T>
	constexpr void DLog(T);
	
	class DebugConsole : public AZ::UTIL::Singleton<DebugConsole>{
		HANDLE hout;
		int hConsole;
		bool DEBUG_TIME;
		int Debug_Line;
		bool UseFlag;
		bool UseHelp;
		
		FILE *fpOut;
		FILE *fpIn;
		
		DWORD NumOfWritten;
		
		void DebugLogLine();
		void SetCodeColor(BYTE);
	public:
		DebugConsole();
		~DebugConsole();
		void SetAttr(WORD);
		void UseTime();
		void UseDebug(bool);
		void Init();
		void Init(std::string);
		void Init(std::wstring);
		
		static constexpr BYTE ID_NONE = 0;
		static constexpr BYTE ID_SAFE = 1;
		static constexpr BYTE ID_WARNING = 2;
		static constexpr BYTE ID_ERROR = 3;
		
		std::string StringShap(BYTE, std::string);
		std::wstring WStringShap(BYTE, std::wstring);
		
		void Log(BYTE type, void*);
		void Log(BYTE type, const char*);
		void Log(BYTE type, std::string);
		void Log(BYTE type, const wchar_t*);
		void Log(BYTE type, std::wstring);
		void Log(BYTE type, unsigned);
		void Log(BYTE type, unsigned long);
		void Log(BYTE type, unsigned long long);
		void Log(BYTE type, signed);
		void Log(BYTE type, signed long);
		void Log(BYTE type, signed long long);
		
		
		template<typename T>
		void CmdLog(T cmd, T msg);
		
		void Help();
		void SetHelp(bool);
		
	private:
		std::vector<std::string> LogVec;
		std::vector<std::wstring> LogVecW;
		std::fstream fs;
		std::wfstream wfs;
		std::string FileName;
		std::wstring WFileName;
		const int cLineNum;
		int LineNum;
		bool WideMode;
	public:
		void ReadLogFile();
		void DisplayLog();
	};
}


namespace Time{
	void NowTime();
}
