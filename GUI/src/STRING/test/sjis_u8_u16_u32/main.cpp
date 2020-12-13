#include"main.hpp"


template<class T>
AZ::String<T>::String(){
	DataCap = DataSize = 0;
	*Data = L'\0';
}

template<class T>
AZ::String<T>::String(const size_t n, const T c){
	wchar_t *tmp = new wchar_t[strlen(c) + 1];
	mbstowcs(tmp, c, 2);
	Data = std::string(n, tmp[0]);
	DataCap = DataSize = Data->size();
	delete [] tmp;
}

template<class T>
AZ::String<T>::String(const char *c){
	wchar_t *tmp = new wchar_t[strlen(c) + 1];
	mbstowcs(tmp, c, strlen(c) + 1);
	Data = tmp;
	DataCap = DataSize = Data->size();
	delete [] tmp;
}

template<class T>
AZ::String<T>::String(std::wstring s){
	Data = new std::wstring(s);
}
template<class T>
AZ::String<T>::String(const wchar_t *wc){
	std::wcout << wc << std::endl;
	Data = new std::wstring(wc);
}
template<class T>
AZ::String<T>::~String(){
	delete Data;
}

int main(){
	
	std::cout << u8"Greek: αβγδ" << std::endl;
	std::cout << u8"日本語出力テスト　🤔 😢 🙇<200d>♂️ 🎉 😰 😊 😭 😥 終端" << std::endl;
	
	AZ::String<std::wstring> str = L"日本語出力テスト　終端　日本語出力テスト";
	std::wcout << str[0];
	
	return 0;
}