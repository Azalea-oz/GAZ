#include"../aaazle.hpp"

#define SJIS 1
#define UTF8 2
#define UTF16 3
#define UTF32 4
#define EUCJP 5


class CODEVI{
	std::string _str;
	static int _ICCode;
	static int _OCCode;
	
	
public:
	CODEVI(int ICCode, int OCCode){
		_ICCode = ICCode;
		_OCCode = OCCode;
		
	}
	~CODEVI(){}
	
	std::string Cvt(std::string str, int Mode){
		
		switch(Mode){
		case SJIS:
			
			break;
		case UTF8:
			break;
		default:
			break;
		}
	}
};
static int CODEVI::_ICCODE = UTF16;
static int CODEVI::_OCCODE = UTF16;

class TW : public AZ::GUI::WINDOW{
	
public:
	TW(int w, int h, std::wstring wstr) : WINDOW(w, h, wstr){
		
	}
	~TW() : WINDOW(){}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	
	
	
}