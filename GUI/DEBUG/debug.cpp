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
	
	DebugConsole::DebugConsole() : DEBUG_TIME(false), Debug_Line(1){
		AllocConsole();
		hout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCtrlHandler(HandlerRoutine, TRUE);
		menu = GetSystemMenu(GetConsoleWindow(), FALSE);
		RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		Log("Wellcome Debug Mode");
	}
	DebugConsole::~DebugConsole(){
		FreeConsole();
	}
	void DebugConsole::SetAttr(WORD attr){
		SetConsoleTextAttribute(hout, attr);
	}
	void DebugConsole::UseTime(){
		Get_Instance().DEBUG_TIME = true;
	}
	
	template<typename T>
	void DebugConsole::Log(T x){
		if(DEBUG_TIME) Time::NowTime();
		DebugLogLine();
		std::cout << "DEBUG Log : ";
		std::cout << std::left << std::setw(30) << x << std::endl;
	}
	template<typename T>
	void DebugConsole::CmdLog(T cmd, T msg){
		if(DEBUG_TIME) Time::NowTime();
		DebugLogLine();
		std::cout << "Command Line " << cmd << " : ";
		std::cout << std::left << std::setw(30) << msg << std::endl;
	}
	
	void DebugConsole:: DebugLogLine(){
		std::cout << "[" << std::right << std::setw(4) << Debug_Line << "]";
		Debug_Line++;
	}
}