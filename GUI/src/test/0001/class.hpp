#include"../../AAAZLE.hpp"
#include<string>
#include"../../CHCODE/chcode.cpp"

class MYWINDOW : public AZ::GUI::WINDOW, private AZ::CUI::CHCODE::UTF8{
	
public:
	MYWINDOW(int, int, std::string);
	~MYWINDOW();
};