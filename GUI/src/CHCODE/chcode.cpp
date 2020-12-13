#include<windows.h>
#include<iostream>
#include<string_view>


namespace AZ{
	namespace CHCODE{
		UTF8::UTF8(std::u8string& u8str){
			str = u8str;
		}
		UTF8::UTF8(std::string&){}
		UTF8::UTF8(std::wstring&){}
		UTF8::~UTF8(){}
		
		bool UTF8::to16(UTF16& u16str){
			auto res = MultiByteToWideChar(
				CP_UTF8, 0,
				reinterpret_cast<const char*>(str.data()),
				reinterpret_cast<int>(str.length()),
				nullptr, 0);
			
			u16str = std::u16string(res, u'\0');
			
			res = MultiByteToWideChar(
				CP_UTF8, 0,
				reinterpret_cast<const char*>(str.data()),
				reinterpret_cast<int>(str.length()),
				u16str.data(), u16str.length());
			
			return res? true:false;
		}
		bool UTF8::to32(UTF32&){}
			
		}
	}
}