#include<windows.h>
#include<iostream>
#include<string>
#include <locale.h>

int main(){
	std::string str;
	std::wstring strW = L"☯☯☯☯";
	char wlocal[strW.length() + 1] = {0x00};
	
	int ret = WideCharToMultiByte(
		CP_ACP, 0,
		strW.c_str(), strW.length(),
		wlocal, strW.length()+1,
		NULL, NULL);
	
	str = wlocal;
	
	setlocale(LC_ALL, "JPN");
	std::wcout << strW << std::endl;
	std::cout << str << std::endl;
	
	
	return 0;
}