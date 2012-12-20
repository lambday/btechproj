#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[] )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if ( ! CreateProcess(
                "f3dPro.exe",
                argv[1],
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi))
        {
            fprintf( stderr, "Create Process failed.\n" );
            return -1;
        }

    WaitForSingleObject( pi.hProcess, INFINITE );
    printf( "Child Complete.\n" );

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    TCHAR szDirectory[MAX_PATH] = "";

    GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
    printf( "Current Directory:%s\n", szDirectory );

    if ( ! CreateProcess(
                "GLPro.exe",
                argv[1],
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi))
        {
            fprintf( stderr, "Create Process failed.\n" );
            return -1;
        }

    WaitForSingleObject( pi.hProcess, INFINITE );
    printf( "Child Complete.\n" );

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    remove( "_iconImage.tmp" );
    remove( "_info2D.tmp" );

    return 0;
}
