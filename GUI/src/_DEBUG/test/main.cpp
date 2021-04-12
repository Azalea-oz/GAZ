#include"main.hpp"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved){
	
	switch(dwReason){
	case DLL_PROCESS_ATTACH:	//アタッチ時
		std::cout << "DLL_PROCESS_ATTACH" << std::endl;
		break;
	case DLL_PROCESS_DETACH:
		std::cout << "DLL_PROCESS_DETACH" << std::endl;
		break;
	}
	
	return true;
}