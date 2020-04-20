#include"AzGui.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	AZ::GUI::WINDOW::INIT(hInstance);
	AZ::GUI::WINDOW::AZWINDOW Azw(800, 600);
	
	//Azw.UseDebug(true);
	Azw.SetClass()->Style(CS_HREDRAW | CS_VREDRAW)->Register();
	
	Azw.Create("�_�͎��񂾁@by �j�[�`�F");
	Azw.Show(nCmdShow);
	
	return Azw.Message();
}