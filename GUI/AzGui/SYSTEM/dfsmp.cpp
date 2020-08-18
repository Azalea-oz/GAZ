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
				std::cout << "�h���C�u" << DInfo[n].DriveName << std::endl;
			}
			void DFSMPInfo::DriveInfomation::PrintDriveTypeToString(int n){
				switch(DInfo[n].DriveType){
				case DRIVE_UNKNOWN:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "�s��";
					break;
				case DRIVE_NO_ROOT_DIR:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "���݂��Ȃ�";
					break;
				case DRIVE_REMOVABLE:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "�����[�o�u���h���C�u";
					break;
				case DRIVE_FIXED:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "�Œ�h���C�u";
					break;
				case DRIVE_REMOTE:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "�����[�g�h���C�u";
					break;
				case DRIVE_CDROM:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "CD/DVD�h���C�u";
					break;
				case DRIVE_RAMDISK:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "RAM�f�B�X�N";
					break;
				default:
					std::cout << std::left << std::setw(30) << "�f�B�X�N�̎��" << std::right << std::setw(13) << "���̑�";
					break;
				}
				std::cout << std::endl;
			}
			
			void DFSMPInfo::DriveInfomation::PrintDriveFreeSpaceToString(int n){
				std::cout << std::left << std::setw(30) << "���p�\\�e��" << std::right << std::setw(11) << BtoGB(DInfo[n].FreeAvailable.QuadPart) << "GB" << std::endl;
				std::cout << std::left << std::setw(30) << "�f�B�X�N�S�̗̂e��" << std::right << std::setw(11) << BtoGB(DInfo[n].Total.QuadPart) << "GB" << std::endl;
				std::cout << std::left << std::setw(30) << "�f�B�X�N�S�̂̋󂫗e��" << std::right << std::setw(11) << BtoGB(DInfo[n].Free.QuadPart) << "GB" << std::endl;
			}
			
			void DFSMPInfo::DriveInfomation::PrintDriveVolumeToString(int n){
				std::cout << std::left << std::setw(30) <<"�{�����[����" << std::right << std::setw(13) << DInfo[n].VolumeName << std::endl;
				std::cout << std::left << std::setw(30) <<"�{�����[���̃V���A���ԍ�" << std::right << std::setw(13) << std::hex <<  DInfo[n].Serial << std::endl;
				std::cout << std::left << std::setw(30) <<"�t�@�C�����̍ő�̒���" << std::right << std::setw(13) << std::dec << DInfo[n].Length << std::endl;
				std::cout << std::left << std::setw(30) <<"�t�@�C���V�X�e���̃I�v�V����" << std::right << std::setw(13) << std::hex << DInfo[n].Flags << std::endl;
				std::cout << std::left << std::setw(30) <<"�t�@�C���V�X�e����" << std::right << std::setw(13) << std::dec << DInfo[n].FileSystemName << std::endl;
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