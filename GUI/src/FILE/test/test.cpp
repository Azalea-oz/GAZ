#include<windows.h>
#include<string>
#include<cstdio>

long long BtKB(long long DataSize){
	return DataSize / 1024;
}
long long BtMB(long long DataSize){
	return DataSize / (1024 * 1024);
}

int main(){
	std::string str = "TestFile.txt";
	
	HANDLE hfile = CreateFileA(
		str.c_str(), GENERIC_READ, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(hfile == INVALID_HANDLE_VALUE){
		puts("can not open file");
		return 0;
	}
	
	switch(GetFileAttributes(str.c_str())){
	case FILE_ATTRIBUTE_NORMAL:
		puts("FILE_ATTRIBUTE_NORMAL");
		break;
	case FILE_ATTRIBUTE_ARCHIVE:
		puts("FILE_ATTRIBUTE_ARCHIVE");
		break;
	case FILE_ATTRIBUTE_READONLY:
		puts("FILE_ATTRIBUTE_READONLY");
		break;
	case FILE_ATTRIBUTE_HIDDEN:
		puts("FILE_ATTRIBUTE_HIDDEN");
		break;
	case FILE_ATTRIBUTE_SYSTEM:
		puts("FILE_ATTRIBUTE_SYSTEM");
		break;
	case FILE_ATTRIBUTE_DIRECTORY:
		puts("FILE_ATTRIBUTE_DIRECTORY");
		break;
	default:
		puts("other");
		break;
	}
	
	FILETIME ft[3];
	GetFileTime(hfile, &ft[0], &ft[1], &ft[2]);
	
	FILETIME lt[3];
	for(int i=0; i<3; i++){
		FileTimeToLocalFileTime(&ft[0], &lt[0]);
		FileTimeToLocalFileTime(&ft[1], &lt[1]);
		FileTimeToLocalFileTime(&ft[2], &lt[2]);
	}
	
	SYSTEMTIME st[3];
	for(int i=0; i<3; i++){
		FileTimeToSystemTime(&lt[0], &st[0]);
		FileTimeToSystemTime(&lt[1], &st[1]);
		FileTimeToSystemTime(&lt[2], &st[2]);
	}
	
	for(int i=0; i<3; i++){
		printf(
			"%04d/%02d/%02d [%d] %02d:%02d:%02d.%03d\n",
			st[i].wYear, st[i].wMonth, st[i].wDay, st[i].wDayOfWeek,
			st[i].wHour, st[i].wMinute, st[i].wSecond, st[i].wMilliseconds);
	}
	
	LARGE_INTEGER Size;
	GetFileSizeEx(hfile, &Size);
	if(Size.QuadPart < 1024){
		printf("File Size : %I64ld[BYTE]\n", Size.QuadPart);
	}else if(BtKB(Size.QuadPart) < 1024){
		printf("File Size : %I64ld[KB]\n", BtKB(Size.QuadPart));
	}else if(BtMB(Size.QuadPart) < 1024){
		printf("File Size : %I64ld[MB]\n", BtMB(Size.QuadPart));
	}
	CloseHandle(hfile);
	return 0;
}