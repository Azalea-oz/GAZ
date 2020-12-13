#include"calc.hpp"

NUMBUTTON::NUMBUTTON() : WINDOW(){}
NUMBUTTON::~NUMBUTTON(){}


CALC::CALC() : WINDOW(400, 500, L"電卓"){
	WClassStyle(CS_HREDRAW | CS_VREDRAW).WClassName(L"Calc").Register();
	WindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE);
}
CALC::~CALC(){}