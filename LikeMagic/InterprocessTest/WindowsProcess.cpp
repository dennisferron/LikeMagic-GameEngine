#include "WindowsProcess.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <stdexcept>

using namespace std;

void create_process(std::string command_line, bool wait_for_completion)
{
    cout << "create process " << command_line << endl;

    STARTUPINFO startup_info;
    PROCESS_INFORMATION process_info;

    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));

    TCHAR* tcmd = new TCHAR[command_line.size()+1];
    std::copy(command_line.begin(), command_line.end(), tcmd);
    tcmd[command_line.size()] = '\0';

    BOOL result = CreateProcess(
        NULL, // No module name - use command line
        tcmd, // Command line
        NULL, // Process handle not inheritable
        NULL, // Thread handle not inheritable
        FALSE, // Set handle inheritance to false
        0,      // No creation flags
        NULL,   // Use parent's environment block
        NULL,   // Use parent's starting directory
        &startup_info, // Pointer to STARTUPINFO structure
        &process_info // Pointer to PROCESS_INFORMATION structure
    );

    if (!result)
    {
        throw std::runtime_error("Could not create process.");
    }
    else
    {
        cout << "Process created." << endl;
    }

    if (wait_for_completion)
    {
        // Wait until child process exits.
        WaitForSingleObject(process_info.hProcess, INFINITE);

        cout << "Process finished." << endl;

        // Close process and thread handles.
        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);
    }
}
