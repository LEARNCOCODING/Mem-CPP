#pragma once
#include <Windows.h>
#include <TlHelp32.h>

//Settings
//MultiByte 
//20 C++ Legacy
//x64

//ProcessHandle -> ProcessId -> GetModuleBaseAddress
//Read<type>(address)
//Write<type>(address,input_value)

class Mem {
private:
    HANDLE ProcHandle;
    DWORD ProcId;

public:
    
    Mem() :ProcHandle(nullptr), ProcId(0) {};

    HANDLE ProcessHandle(LPCSTR ProcessName)
    {
        HWND hwnd = FindWindowA(NULL, ProcessName);
        GetWindowThreadProcessId(hwnd, &ProcId);
        ProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcId);
        return ProcHandle;
    }

    DWORD ProcessId()
    {
        return ProcId;
    }

    uintptr_t GetModuleBaseAddress(DWORD processId, const char* moduleName)
    {
        uintptr_t moduleBaseAddress = 0;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 moduleEntry32;
            moduleEntry32.dwSize = sizeof(MODULEENTRY32);
            if (Module32First(hSnapshot, &moduleEntry32)) {
                do {
                    if (strcmp(moduleEntry32.szModule, moduleName) == 0) {
                        moduleBaseAddress = (uintptr_t)moduleEntry32.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnapshot, &moduleEntry32));
            }
            CloseHandle(hSnapshot);
        }
        return moduleBaseAddress;
    }

    ~Mem() {
        CloseHandle(ProcHandle);
    }

    template<typename T>
    T Read(DWORD_PTR address) {
        T buffer;
        ReadProcessMemory(ProcHandle, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), nullptr);
        return buffer;
    }

    template<typename T>
    void Write(DWORD_PTR address, T value) {
        WriteProcessMemory(ProcHandle, reinterpret_cast<LPVOID>(address), &value, sizeof(T), nullptr);
    }

};