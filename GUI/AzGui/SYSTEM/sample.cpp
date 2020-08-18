#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

// メイン関数
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
        
        // モジュール数
        if ( Module32First(hSnapshot,&me32) ){
            do {
                nModule++;
            } while ( Module32Next(hSnapshot,&me32) );
        }
        // スレッド数
        if ( Thread32First(hSnapshot,&te32) ){
            do {
                nThread++;
            } while ( Thread32Next(hSnapshot,&te32) );
        }
        // プロセス数
        if ( Process32First(hSnapshot,&pe32) ){
            do {
                nProccess++;
            } while ( Process32Next(hSnapshot,&pe32) );
        }
        CloseHandle( hSnapshot );
    }
    printf( "モジュール数：%d個\n", nModule );
    printf( "スレッド数：%d個\n", nThread );
    printf( "プロセス数：%d個\n", nProccess );
    return 0;
}