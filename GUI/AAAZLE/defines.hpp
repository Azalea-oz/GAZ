#define ID_BUTTON 10000
#define IDM_END   10001
#define IDM_ON    10002
#define IDM_OFF   10003

#define AZ_RELATIVE_SIZE 0x4005

#include<string>

#if defined(_UNICODE) || defined(UNICODE)
#define tcout std::wcout
#else
#define tcout std::cout
#endif

typedef std::basic_string<TCHAR> tstring;