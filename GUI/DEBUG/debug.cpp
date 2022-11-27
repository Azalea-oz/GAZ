#include"debug.hpp"
#include"util.hpp"

#define DGLOG(x) DEBUG::DebugConsole::Get_Instance().Log(x)
#define DGDIALOG(x) DEBUG::error_dialog(x);





BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved){
	
	switch(dwReason){
	case DLL_PROCESS_ATTACH:	//アタッチ時
		//DEBUG::DebugConsole::Get_Instance().Init();
		
		break;
	case DLL_PROCESS_DETACH:	//デタッチ時
		//unhook
		//UnhookWindowsHookEx();
		break;
	}
	
	return true;
}


namespace DEBUG{
	
	void error_dialog(HWND hwnd, std::string str){
		LPVOID err_msg;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&err_msg, 0, NULL);
		
		MessageBox(hwnd, (LPCTSTR)err_msg, str.c_str(), MB_OK);
		LocalFree(err_msg);
	}
	void error_dialog(HWND hwnd, std::wstring str){
		LPVOID err_msg;
		FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&err_msg, 0, NULL);
		
		MessageBoxW(hwnd, (LPCWSTR)err_msg, str.c_str(), MB_OK);
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
	
	DebugConsole::DebugConsole() : DEBUG_TIME(false), Debug_Line(1), UseHelp(true), cLineNum(256){UseFlag = false;}
	DebugConsole::~DebugConsole(){
		//std::cout << "Close console" << std::endl;
		std::wcout << L"Close console" << std::endl;
		if(FileName.length()){
			if(WideMode){
				wfs.open(DEBUG::UTIL::WStoS(WFileName), std::ios_base::out | std::ios_base::app);
				if(wfs){
					LogVec.push_back("\n");
					for(auto Str : LogVecW){
						//std::cout << Str;
						wfs << Str;
					}
					
					wfs.close();
					Log(ID_NONE, std::wstring(L"Log File [") + WFileName + L"]");
				} else{
					std::wcout << L"Can not open [" << WFileName << L"]" << std::endl;
				}
			} else{
				fs.open(FileName, std::ios_base::out | std::ios_base::app);
				if(fs){
					LogVec.push_back("\n");
					for(auto Str : LogVec){
						//std::cout << Str;
						fs << Str;
					}
					
					fs.close();
				} else{
					std::cout << "Can not open [" << FileName << "]" << std::endl;
				}
			}
		}
		
		_close(hConsole);
		FreeConsole();
	}
	void DebugConsole::SetAttr(WORD attr){if(UseFlag) SetConsoleTextAttribute(hout, attr);}
	void DebugConsole::UseTime(){if(UseFlag) Get_Instance().DEBUG_TIME = true;}
	
	void DebugConsole::Init(){
		//DEBUG::error_dialog(NULL, "Init");
		std::string tmp;
		if(!UseFlag){
			WideMode = true;
			
			AllocConsole();
			SetConsoleTitle("DEBUG Console");
			hConsole = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
			SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
			*stdout = *_fdopen(hConsole, "w");
			setvbuf(stdout, NULL, _IONBF, 0);
			UseFlag = true;
			hout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Log(ID_NONE, "Wellcome Debug Mode");
			if(UseHelp)Help();
			DisplayLog();
		} else{
			Log(ID_WARNING, "Console was opend");
		}
	}
	void DebugConsole::Init(std::string filename){
		//DEBUG::error_dialog(NULL, "Init");
		std::string tmp;
		if(!UseFlag){
			WideMode = false;
			FileName = filename;
			
			AllocConsole();
			SetConsoleTitle("DEBUG Console");
			hConsole = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
			SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
			*stdout = *_fdopen(hConsole, "w");
			setvbuf(stdout, NULL, _IONBF, 0);
			UseFlag = true;
			hout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Log(ID_NONE, "Wellcome Debug Mode");
			if(UseHelp)Help();
			
			fs.open(FileName, std::ios_base::in);
			if(fs.is_open()){
				ReadLogFile();
				fs.close();
			} else{
				fs.open(FileName, std::ios_base::out);
				fs.close();
			}
			Log(ID_NONE, std::string("Log File [") + FileName + "]");
			DisplayLog();
		} else{
			Log(ID_WARNING, "Console was opend");
		}
	}
	void DebugConsole::Init(std::wstring filename){
		//DEBUG::error_dialog(NULL, "Init");
		std::string tmp;
		if(!UseFlag){
			WideMode = true;
			WFileName = filename;
			
			AllocConsole();
			SetConsoleTitle("DEBUG Console");
			hConsole = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
			SetConsoleCtrlHandler(HandlerRoutine, TRUE);
			HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
			RemoveMenu(menu, SC_CLOSE, MF_BYCOMMAND);
			*stdout = *_fdopen(hConsole, "w");
			setvbuf(stdout, NULL, _IONBF, 0);
			UseFlag = true;
			hout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Log(ID_NONE, "Wellcome Debug Mode");
			if(UseHelp)Help();
			
			wfs.open(UTIL::WStoS(WFileName), std::ios_base::in);
			if(wfs.is_open()){
				ReadLogFile();
				wfs.close();
			} else{
				wfs.open(UTIL::WStoS(WFileName), std::ios_base::out);
				wfs.close();
			}
			Log(ID_NONE, std::wstring(L"Log File [") + WFileName + L"]");
			DisplayLog();
		} else{
			Log(ID_WARNING, "Console was opend");
		}
	}
	void DebugConsole::ReadLogFile(){
		if(WideMode){
			std::wstring buffer;
			while(!wfs.eof()){
				std::getline(wfs, buffer);
				buffer += L"\n";
				LogVecW.push_back(buffer);
				if(cLineNum < LogVec.size()) LogVec.erase(LogVec.begin() + 0);
			}
			LogVec.pop_back();
			LogVec.pop_back();
			Debug_Line = std::stoi(LogVec.back().substr(LogVecW.back().find_first_of(L"[") + 1, LogVecW.back().find_first_of(L"]") - 1).c_str()) + 1;
		} else{
			std::string buffer;
			while(!fs.eof()){
				std::getline(fs, buffer);
				buffer += "\n";
				LogVec.push_back(buffer);
				if(cLineNum < LogVec.size()) LogVec.erase(LogVec.begin() + 0);
			}
			LogVec.pop_back();
			LogVec.pop_back();
			Debug_Line = std::atoi(LogVec.back().substr(LogVec.back().find_first_of("[") + 1, LogVec.back().find_first_of("]") - 1).c_str()) + 1;
		}
	}
	void DebugConsole::DisplayLog(){
		if(LogVec.size() != 0) for(auto Str : LogVec) std::cout << Str;
	}
	
	std::string DebugConsole::StringShap(BYTE type, std::string str){
		if(DEBUG_TIME) Time::NowTime();
		DebugLogLine();
		SetCodeColor(type);
		std::ostringstream oss;
		oss.setf(std::ios::left);
		oss.fill(' ');
		oss.width(30);
		oss << str;
		return oss.str();
	}
	std::wstring DebugConsole::WStringShap(BYTE type, std::wstring str){
		if(DEBUG_TIME) Time::NowTime();
		DebugLogLine();
		SetCodeColor(type);
		std::wostringstream oss;
		oss.setf(std::ios::left);
		oss.fill(L' ');
		oss.width(30);
		oss << str;
		return oss.str();
	}
	
	void DebugConsole::Log(BYTE type, void *x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring((long long)x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string((long long)x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, const char *x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = UTIL::StoWS(std::string(x));
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = x;
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	
	
	void DebugConsole::Log(BYTE type, std::string x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = UTIL::StoWS(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = x;
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, const wchar_t *x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = x;
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = UTIL::WStoS(std::wstring(x));
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, std::wstring x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = x;
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = UTIL::WStoS(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, unsigned x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, unsigned long x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, unsigned long long x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, signed x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, signed long x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
	}
	void DebugConsole::Log(BYTE type, signed long long x){
		if(UseFlag){
			if(WideMode){
				std::wstring tmp = std::to_wstring(x);
				tmp = WStringShap(type, tmp);
				tmp += L'\n';
				LogVecW.push_back(tmp);
				WriteConsoleW(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			} else{
				std::string tmp = std::to_string(x);
				tmp = StringShap(type, tmp);
				tmp += '\n';
				LogVec.push_back(tmp);
				WriteConsole(
					hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
				SetAttr(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
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
	
	void DebugConsole::DebugLogLine(){
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
				hout, tmp.c_str(), tmp.length(), &NumOfWritten, NULL);
			Debug_Line++;
		}
	}
	void DebugConsole::SetCodeColor(BYTE type){
		switch(type){
 		case ID_NONE:
			SetAttr(FOREGROUND_WHITE); break;
		case ID_SAFE:
			SetAttr(FOREGROUND_BLUE_H);
			std::cout << "SAFE : ";
			break;
		case ID_WARNING:
			SetAttr(FOREGROUND_YELLOW_H);
			std::cout << "WARN : ";
			break;
		case ID_ERROR:
			SetAttr(FOREGROUND_RED_H);
			std::cout << "ERROR : ";
			break;
		}
	}
	void DebugConsole::Help(){
		Log(ID_NONE, L"NONE : ID_NONE outputs a log without warning.");
		Log(ID_SAFE, L"ID_SAFE outputs a log of normal operation in light blue.");
		Log(ID_WARNING, L"ID_WARNING outputs a log of warning operation in yellow.");
		Log(ID_ERROR, L"ID_ERROR outputs a log of critical error in red.");
	}
	void DebugConsole::SetHelp(bool f){
		UseHelp = f;
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