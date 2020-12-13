#include<windows.h>
#include<iostream>
#include<string_view>


namespace AZ{
	namespace CHCODE{
		class UTF8{
			std::basic_string<char8_t> str;
			
		public:
			UTF8(char8_t);
			UTF8(std::string);
			UTF8(std::wstring);
			~UTF8();
			
			bool to16(UTF16&);
			bool to32(UTF32&);
			
		}
	}
}