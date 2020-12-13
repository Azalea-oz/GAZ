#include<iostream>
#include<string>
#include<windows.h>
#include <fcntl.h>


namespace AZ{
	
	template<class T>
	class String{
		std::wstring *Data;
		size_t DataCap;
		size_t DataSize;
	public:
		//constructor
		String();
		String(const size_t, const T);
		String(const char *);
		String(const std::wstring);
		String(const wchar_t *);
		~String();
		
		//operator
		const wchar_t& operator[](const size_t n) const{
			return (*Data)[n];
		}
		wchar_t& operator[](const size_t n){
			std::wcout << (*Data)[0] << std::endl;
			return (*Data)[n];
		}
	};
	
	namespace cvt{
		std::string wtu8(const std::wstring &wstr){
			if(wstr.empty()) return std::string();
			int StrLen = WideCharToMultiByte(
				CP_UTF8, 0, &wstr[0], (int)wstr.size(),
				nullptr, 0, nullptr, nullptr);
			
			std::string str(StrLen, 0);
			WideCharToMultiByte(
				CP_UTF8, 0, &wstr[0], (int)wstr.size(),
				&str[0], StrLen, nullptr, nullptr);
			return str;
		}
		
		std::wstring u8tw(const std::string &str){
			if(str.empty()) return std::wstring();
			int StrLen = MultiByteToWideChar(
				CP_UTF8, 0, &str[0], (int)str.size(),
				nullptr, 0);
			
			std::wstring wstr(StrLen, 0);
			MultiByteToWideChar(
				CP_UTF8, 0, &str[0], (int)wstr.size(),
				&wstr[0], StrLen);
			return wstr;
		}
	};
};