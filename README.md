.NET profiler DLL loading can be abused to make a legit .NET application load a malicious DLL using environment variables. This exploit is loading a malicious DLL using Task Scheduler (MMC) to bypass UAC and getting admin privileges.

CLR uses the COR_PROFILER_PATH environment variable to find the DLL, If this path is not defined it looks for CLSID to load DLL. In this scenario, we created three enviornment variables under user (HKCU). COR_PROFILER_PATH is reffering our malicious DLL, So when we execute any .NET application (which always execute as High IL without UAC prompt) to load our dll to bypass UAC prompt and can get High IL (Admin Privileges).
* COR_ENABLE_PROFILING=1
* COR_PROFILER={A2D4B6C7-1234-5678-9ABC-DEF012345678}
* COR_PROFILER_PATH=C:\Users\Public\led.dll



https://github.com/user-attachments/assets/c61670fb-c1ef-46db-a1de-557b8104172c



# Usage 
1) Place compiled DLL (led.dll) in "C:\Users\Public" folder.
2) Build project using Visual Studio and execute compiled binary.
3) You will get admin shell, DLL is executing command to open cmd.exe.
4) Tested on Windows 11 pro, 23H2

# Disclaimer
Only for educational Purposes.

### REF.
* https://offsec.almond.consulting/UAC-bypass-dotnet.html
* https://blog.talosintelligence.com/deep-dive-into-phobos-ransomware/
