#include<iostream>
#include<string>
#include<locale>


int main(){
	
	/*
	std::ios_base::sync_with_stdio(false);
	std::locale default_loc("");
	std::locale::global(default_loc);
	std::locale ctype_default(std::locale::classic(), default_loc, std::locale::ctype);
	std::wcout.imbue(ctype_default);
	std::wcin.imbue(ctype_default);
	*/
	//setlocale( LC_ALL, ".utf8" );
	setlocale( LC_ALL, "ja_JP.UTF-8" );
	//std::wcout.imbue( std::locale( "", std::locale::ctype ) );
	
	std::cout << "aiueo " << std::endl;
	std::cout << 12345<< std::endl;
	std::cout << "あいうえお" << std::endl;
	std::wcout << L"waiueo" << std::endl;
	std::wcout << 12345<< std::endl;
	std::wcout << L"😊😊😊😊" << std::endl;
	
	return 0;
}