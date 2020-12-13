#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

// ���C���֐�
int main( void )
{
    DWORD   dwPID = GetCurrentProcessId();
    HANDLE  hSnapshot;
    INT     nModule   = 0;
    INT     nThread   = 0;
    INT     nProccess = 0;
    
    if ( (hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL,dwPID)) != INVALID_HANDLE_VALUE ){
        MODULEENTRY32  me32 = { sizeof(MODULEENTRY32) };
        THREADENTRY32  te32 = { sizeof(THREADENTRY32) };
        PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
        
        // ���W���[����
        if ( Module32First(hSnapshot,&me32) ){
            do {
                nModule++;
            } while ( Module32Next(hSnapshot,&me32) );
        }
        // �X���b�h��
        if ( Thread32First(hSnapshot,&te32) ){
            do {
                nThread++;
            } while ( Thread32Next(hSnapshot,&te32) );
        }
        // �v���Z�X��
        if ( Process32First(hSnapshot,&pe32) ){
            do {
                nProccess++;
            } while ( Process32Next(hSnapshot,&pe32) );
        }
        CloseHandle( hSnapshot );
    }
    printf( "���W���[�����F%d��\n", nModule );
    printf( "�X���b�h���F%d��\n", nThread );
    printf( "�v���Z�X���F%d��\n", nProccess );
    return 0;
}