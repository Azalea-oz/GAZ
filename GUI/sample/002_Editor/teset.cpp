#include<cstdio>
#include<string>
#include<iostream>

int main(){
	FILE *fp;
	std::wstring str;
	
	if(!(fp = _wfopen(L"html_sample.html", L"r"))){
		wprintf(L"Can not open file\n");
		return 0;
	}
	
	wchar_t tmp[256] = L"\0";
	
	while(1){
		if(!fgetws(tmp, 256, fp)){
			break;
		}
		
		str += tmp;
		str.pop_back();
		str += L"\r\n";
	}
	
	std::wcout << str;
	
	fclose(fp);
	return 0;
}