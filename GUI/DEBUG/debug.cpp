#include"debug.hpp"

#if defined(USEDEBUG)
#define DEBUGMODE 1
#else
#define DEBUGMODE 0
#endif

namespace DEBUG{
	
	void error_dialog(HWND hwnd){
		LPVOID err_msg;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&err_msg, 0, NULL);
		
		MessageBox(hwnd, (LPCTSTR)err_msg, "ERROR", MB_OK);
		LocalFree(err_msg);
	}
	
	
	BOOL WINAPI HandlerRoutine(DWORD dwCtrlType){
		if(dwCtrlType == CTRL_C_EVENT){
			FreeConsole();
			return TRUE;
		}
		
		return FALSE;
	}
	template<typename T>
	constexpr void DLog(T x){
		MessageBox(NULL, TEXT(x), TEXT("DEBUG"), MB_OK);
	}
	
	DebugConsole::DebugConsole() : DEBUG_TIME(false), Debug_Line(1){
		if(DEBUGMODE){
			UseFlag = false;
		}
	}
	DebugConsole::~DebugConsole(){if(UseFlag) FreeConsole();}
	void DebugConsole::SetAttr(WORD attr){if(UseFlag) SetConsoleTextAttribute(hout, attr);}
	void DebugConsole::UseTime(){if(UseFlag) Get_Instance().DEBUG_TIME = true;}
	
	void DebugConsole::Init(){
		if(!UseFlag){
			AllocConsole();
			hout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
			freopen("CONOUT$", "w", stdout);
			freopen("CONIN$", "r", stdin);
			setlocale(LC_ALL, "Japanese");
			Log("Wellcome Debug Mode");
			UseFlag = true;
		}
	}
	template<typename T>
	void DebugConsole::Log(T x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}

	template<> void DebugConsole::Log<std::string>(std::string x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<char *>(char *x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<unsigned long>(unsigned long x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<unsigned int>(unsigned int x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<int>(int x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<void*>(void* x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "DEBUG Log : ";
			std::cout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<std::wstring>(std::wstring x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::wcout << "DEBUG Log : ";
			std::wcout << x << std::endl;
		}
	}
	template<> void DebugConsole::Log<wchar_t const *>(wchar_t const *x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::wcout << "DEBUG Log : ";
			std::wcout << x << std::endl;
		}
	}
	
	
	template<typename T>
	void DebugConsole::CmdLog(T cmd, T msg){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::cout << "Command Line " << cmd << " : ";
			std::cout << std::left << std::setw(30) << msg << std::endl;
		}
	}
	
	void DebugConsole:: DebugLogLine(){
		if(UseFlag){
			std::cout << "[" << std::right << std::setw(4) << Debug_Line << "]";
			Debug_Line++;
		}
	}
}

namespace Time{
	void NowTime(){
		time_t t = time(0);
		tm *now = localtime(&t);
		std::cout << "[" << now->tm_year + 1900
				  << "/" << now->tm_mon + 1
				  << "/" << now->tm_mday
				  << " " << now->tm_hour
				  << ":" << now->tm_min
				  << ":" << now->tm_sec << "]" << " ";
	}
}