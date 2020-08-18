#include"../../AAAZLE.hpp"
#define ID_BUTTON2 1201

#define USE_DEBUG (1)

class MYWINDOW : public AZ::GUI::WINDOW{
public:
	MYWINDOW(int, int);
	MYWINDOW(int, int, std::string);
	MYWINDOW(int, int, std::wstring);
	~MYWINDOW();
	
	AZ::GUI::CODE ECLOSE(const HWND, const UINT, const WPARAM, const LPARAM);
};

class BTNWINDOW : public AZ::GUI::WINDOW{
public:
	BTNWINDOW(int, int);
	BTNWINDOW(int, int, std::string);
	BTNWINDOW(int, int, std::wstring);
	~BTNWINDOW();
	
	AZ::GUI::CODE ECOMMAND(const HWND, const UINT, const WPARAM, const LPARAM);
	
	AZ::GUI::CODE EVENT(const HWND, const UINT, const WPARAM, const LPARAM);
};