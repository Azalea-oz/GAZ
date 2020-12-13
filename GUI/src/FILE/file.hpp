#include<windows.h>
#include<string>
#include"../GUI/gui.hpp"

namespace AZ{
	namespace SYSTEM{
		namespace FILE{
			/*
			class SINFO{
				hFile;
			public:
				SINFO();
				SINFO(std::string);
				SINFO(std::wstring);
				~SINFO();
				
				bool Open(std::string);
				bool Open(std::wstring);
				bool Close();
				
				long long int GetFileSize();
					
			};
			*/
			
			class SFILE{
				
				CODE DDFILE(const HWND, const UINT, const WPARAM, const LPARAM);
			public:
				SFILE(GUI::WINDOW*);
				~SFILE();
			};
		}
	}
}