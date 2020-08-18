#include"../../AAAZLE.hpp"


class TIMERWINDOW : public AZ::GUI::WINDOW{
	
	
public:
	TIMERWINDOW(int, int, std::string);
	TIMERWINDOW(int, int, std::wstring);
	~TIMERWINDOW();
	
	
};


class TIMERCOMPO : public AZ::GUI::WINDOW{
	
	
public:
	TIMERCOMPO(int, int, std::string);
	TIMERCOMPO(int, int, std::wstring);
	~TIMERCOMPO();
	
	
};