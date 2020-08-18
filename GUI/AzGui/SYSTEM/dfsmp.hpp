// d drive
// f file
// s system
// m memory
// p process
// 
// 


#include<windows.h>
#include<tchar.h>
#include<iostream>
#include <iomanip>
#include"../defines.hpp"
#include"../ERR/err.hpp"

#define BtoMB(x) x/1024/1024
#define BtoGB(x) x/1024/1024/1024

typedef struct{
	tstring DriveName;
	tstring VolumeName;
	DWORD Serial;
	DWORD Length;
	DWORD Flags;
	tstring FileSystemName;
	DWORD DriveType;
	ULARGE_INTEGER FreeAvailable;
	ULARGE_INTEGER Total;
	ULARGE_INTEGER Free;
} DriveInfo, *PDriveInfo;

namespace AZ{
	namespace GUI{
		namespace DFSMP{
			
			class DFSMPInfo{
				
				
			public:
				
				
				
				class DriveInfomation{
					PDriveInfo DInfo;
					tstring RootPathName;
					
					int DriveNums;
					
					void PrintDriveNameToString(int);
					void PrintDriveTypeToString(int);
					void PrintDriveFreeSpaceToString(int);
					void PrintDriveVolumeToString(int n);
				public:
					DriveInfomation();
					~DriveInfomation();
					
					int GetDriveNameArray();
					void GetDriveTypes(int);
					void GetDriveFreeSpace(int);
					void GetDriveVolumeInfo(int);
					void Print();
					
				} DInfo;
			};
			
			class WindowsInfo{
				
			public:
				Get
			};
		}
	}
}