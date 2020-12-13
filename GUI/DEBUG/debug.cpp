#include"debug.hpp"


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
	
	DebugConsole::DebugConsole() : DEBUG_TIME(false), Debug_Line(1){UseFlag = false;}
	DebugConsole::~DebugConsole(){if(UseFlag) FreeConsole();}
	void DebugConsole::SetAttr(WORD attr){if(UseFlag) SetConsoleTextAttribute(hout, attr);}
	void DebugConsole::UseTime(){if(UseFlag) Get_Instance().DEBUG_TIME = true;}
	
	void DebugConsole::Init(){
		std::string tmp;
		if(!UseFlag){
			AllocConsole();
			hout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
			freopen("CONOUT$", "w", stdout);
			freopen("CONIN$", "r", stdin);
			UseFlag = true;
			Log("Wellcome Debug Mode");
		} else{
			Log("Console was opend");
		}
	}
	template<typename T>
	void DebugConsole::Log(T x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
		
	}

	
	template<> void DebugConsole::Log<std::string>(std::string x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<char *>(char *x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<unsigned long>(unsigned long x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<unsigned int>(unsigned int x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<int>(int x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<void*>(void* x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::ostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::string tmp;
			tmp += oss.str();
			tmp += '\n';
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<std::wstring>(std::wstring x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::wostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::wstring tmp;
			tmp += oss.str();
			tmp += L'\n';
			WriteConsoleW(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.size(), &NumOfWritten, NULL);
		}
	}
	template<> void DebugConsole::Log<wchar_t const *>(wchar_t const *x){
		if(UseFlag){
			if(DEBUG_TIME) Time::NowTime();
			DebugLogLine();
			std::wostringstream oss;
			oss.setf(std::ios::left);
			oss.fill(' ');
			oss.width(30);
			oss << x;
			std::wstring tmp;
			tmp += oss.str();
			tmp += L'\n';
			WriteConsoleW(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.size(), &NumOfWritten, NULL);
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
			std::ostringstream oss;
			oss.setf(std::ios::right);
			oss.fill(' ');
			oss.width(4);
			oss << Debug_Line;
			std::string tmp = "[";
			tmp += oss.str();
			tmp += "]";
			WriteConsole(
				GetStdHandle(STD_OUTPUT_HANDLE), 
				tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
			Debug_Line++;
		}
	}
}

namespace Time{
	void NowTime(){
		time_t t = time(0);
		tm *now = localtime(&t);
		std::string tmp = "[";
		tmp += now->tm_year + 1900;
		tmp += '/';
		tmp += now->tm_mon + 1;
		tmp += '/';
		tmp += now->tm_mday;
		tmp += ' ';
		tmp += now->tm_hour;
		tmp += ':';
		tmp += now->tm_min;
		tmp += ':';
		tmp += now->tm_sec;
		tmp += "] ";
	}
}