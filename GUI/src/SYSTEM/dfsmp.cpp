#include"dfsmp.hpp"

namespace AZ{
	namespace GUI{
		namespace DFSMP{
			
			DFSMPInfo::DriveInfomation::DriveInfomation(){
				DriveNums = GetDriveNameArray();
				
				for(int n = 0; n < DriveNums; n++){
					GetDriveVolumeInfo(n);
					GetDriveTypes(n);
					GetDriveFreeSpace(n);
				}
				
			}
			DFSMPInfo::DriveInfomation::~DriveInfomation(){
				delete DInfo;
			}
			
			int DFSMPInfo::DriveInfomation::GetDriveNameArray(){
				//Get Logical Drives
				char *DriveNameBuffer;
				int DriveBufferBytes = GetLogicalDriveStrings(0, DriveNameBuffer);
				DriveNameBuffer = new char[DriveBufferBytes+1];
				
				if(GetLogicalDriveStrings(DriveBufferBytes, DriveNameBuffer) <= 0){
					std::cerr << "GetLogicalDriveStrings failed" << std::endl;
					AZ::GUI::ERR::Print();
					return 0;
				}
				
				DInfo = new DriveInfo[DriveBufferBytes];
				int TotalDirveNums = 0;
				for(char *p = DriveNameBuffer; *p != '\0'; p += strlen(p) + 1, TotalDirveNums++){
					DInfo[TotalDirveNums].DriveName = p;
					//std::cout << TotalDirveNums << " : " << DInfo[TotalDirveNums].DriveName << std::endl;
				}
				delete DriveNameBuffer;
				return TotalDirveNums;
			}
			
			void DFSMPInfo::DriveInfomation::GetDriveTypes(int n){
				DInfo[n].DriveType = GetDriveType(DInfo[n].DriveName.c_str());
			}
			void DFSMPInfo::DriveInfomation::GetDriveFreeSpace(int n){
				GetDiskFreeSpaceEx(DInfo[n].DriveName.c_str(), &(DInfo[n].FreeAvailable), &(DInfo[n].Total), &(DInfo[n].Free));
			}
			void DFSMPInfo::DriveInfomation::GetDriveVolumeInfo(int n){
				char VNtmp1[256], VNtmp2[256];
				if(!GetVolumeInformation(
						DInfo[n].DriveName.c_str(),
						VNtmp1, MAX_PATH + 1,
						&DInfo[n].Serial,
						&DInfo[n].Length,
						&DInfo[n].Flags,
						VNtmp2,
						MAX_PATH + 1)){
					DInfo[n].Serial = 0;
					DInfo[n].Length = 0;
					DInfo[n].Flags = 0;
				}
				
				DInfo[n].VolumeName = VNtmp1;
				DInfo[n].FileSystemName = VNtmp2;
			}
			
			void DFSMPInfo::DriveInfomation::PrintDriveNameToString(int n){
				std::cout << "ドライブ" << DInfo[n].DriveName << std::endl;
			}
			void DFSMPInfo::DriveInfomation::PrintDriveTypeToString(int n){
				switch(DInfo[n].DriveType){
				case DRIVE_UNKNOWN:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "不明";
					break;
				case DRIVE_NO_ROOT_DIR:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "存在しない";
					break;
				case DRIVE_REMOVABLE:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "リムーバブルドライブ";
					break;
				case DRIVE_FIXED:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "固定ドライブ";
					break;
				case DRIVE_REMOTE:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "リモートドライブ";
					break;
				case DRIVE_CDROM:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "CD/DVDドライブ";
					break;
				case DRIVE_RAMDISK:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "RAMディスク";
					break;
				default:
					std::cout << std::left << std::setw(30) << "ディスクの種類" << std::right << std::setw(13) << "その他";
					break;
				}
				std::cout << std::endl;
			}
			
			void DFSMPInfo::DriveInfomation::PrintDriveFreeSpaceToString(int n){
				std::cout << std::left << std::setw(30) << "利用可能\容量" << std::right << std::setw(11) << BtoGB(DInfo[n].FreeAvailable.QuadPart) << "GB" << std::endl;
				std::cout << std::left << std::setw(30) << "ディスク全体の容量" << std::right << std::setw(11) << BtoGB(DInfo[n].Total.QuadPart) << "GB" << std::endl;
				std::cout << std::left << std::setw(30) << "ディスク全体の空き容量" << std::right << std::setw(11) << BtoGB(DInfo[n].Free.QuadPart) << "GB" << std::endl;
			}
			
			void DFSMPInfo::DriveInfomation::PrintDriveVolumeToString(int n){
				std::cout << std::left << std::setw(30) <<"ボリューム名" << std::right << std::setw(13) << DInfo[n].VolumeName << std::endl;
				std::cout << std::left << std::setw(30) <<"ボリュームのシリアル番号" << std::right << std::setw(13) << std::hex <<  DInfo[n].Serial << std::endl;
				std::cout << std::left << std::setw(30) <<"ファイル名の最大の長さ" << std::right << std::setw(13) << std::dec << DInfo[n].Length << std::endl;
				std::cout << std::left << std::setw(30) <<"ファイルシステムのオプション" << std::right << std::setw(13) << std::hex << DInfo[n].Flags << std::endl;
				std::cout << std::left << std::setw(30) <<"ファイルシステム名" << std::right << std::setw(13) << std::dec << DInfo[n].FileSystemName << std::endl;
			}
			
			void DFSMPInfo::DriveInfomation::Print(){
				for(int n = 0; n < DriveNums; n++){
					PrintDriveNameToString(n);
					PrintDriveVolumeToString(n);
					PrintDriveTypeToString(n);
					PrintDriveFreeSpaceToString(n);
					std::cout << std::endl;
				}
			}
		}
	}
}