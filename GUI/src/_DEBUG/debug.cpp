#include"debug.hpp"

#define DGLOG(x) DEBUG::DebugConsole::Get_Instance().Log(x)
#define DGDIALOG(x) DEBUG::error_dialog(x);





BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved){
	
	switch(dwReason){
	case DLL_PROCESS_ATTACH:	//アタッチ時
		DEBUG::DebugConsole::Get_Instance();
		
		break;
	case DLL_PROCESS_DETACH:	//デタッチ時
		//unhook
		UnhookWindowsHookEx();
		break;
	}
	
	return true;
}


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
	DebugConsole::~DebugConsole(){
		_close(hConsole);
		FreeConsole();
	}
	void DebugConsole::SetAttr(WORD attr){if(UseFlag) SetConsoleTextAttribute(hout, attr);}
	void DebugConsole::UseTime(){if(UseFlag) Get_Instance().DEBUG_TIME = true;}
	
	void DebugConsole::Init(){
		DEBUG::error_dialog(NULL);
		std::string tmp;
		if(!UseFlag){
			AllocConsole();
			SetConsoleTitle("DEBUG Console");
			hConsole = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
			SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
			*stdout = *_fdopen(hConsole, "w");
			setvbuf(stdout, NULL, _IONBF, 0);
			UseFlag = true;
			Log("Wellcome Debug Mode");
		} else{
			Log("Console was opend");
		}
	}
	template<typename T>
	void DebugConsole::Log(T x){
		DEBUG::error_dialog(NULL);
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
		DEBUG::error_dialog(NULL);
	}

	template void DebugConsole::Log<char const*>(char const*);
	template void DebugConsole::Log<unsigned long>(unsigned long);
	template void DebugConsole::Log<unsigned int>(unsigned int);
	template void DebugConsole::Log<int>(int);
	template void DebugConsole::Log<void*>(void*);
	
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