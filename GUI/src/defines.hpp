#define ID_BUTTON 10000
#define IDM_END   10001
#define IDM_ON    10002
#define IDM_OFF   10003

#define AZ_RELATIVE_SIZE 0x4005
#define AZ_RESIZE 0x4006

#include<string>

#define STR_ENCODE_SJIS 1
#define STR_ENCODE_EUCJP 2
#define STR_ENCODE_UNICODE 3


#ifdef AZ_STR_ENCODE
	#if defined(_UNICODE) || defined(UNICODE)
	#undef AZ_STR_ENCODE
	#define AZ_STR_ENCODE STR_ENCODE_UNICODE
	#endif
#else
	#define AZ_STR_ENCODE STR_ENCODE_UNICODE
#endif

#if AZ_STR_ENCODE == 2
	#error String encode type is euc-jp.
#endif
#if AZ_STR_ENCODE > 4 || AZ_STR_ENCODE < 1
	#error String encode type is out of range
#endif

#if defined(_UNICODE) || defined(UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

typedef std::basic_string<TCHAR> tstring;

#define DEFAULTEVE 1
#define STOPEVE 0

#define AZMAIN(hinst, hprev, lpcmd, ncmd) int WINAPI WinMain(HINSTANCE (hinst), HINSTANCE (hprev), LPSTR (lpcmd), int (ncmd))
#define WAZMAIN(hinst, hprev, lpcmd, ncmd) int WINAPI wWinMain(HINSTANCE (hinst), HINSTANCE (hprev), LPWSTR (lpcmd), int (ncmd))

#define CreateMsgMacro(x) (HMENU)WM_APP + (x)