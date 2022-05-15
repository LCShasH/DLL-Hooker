#include "hooks.hpp"

#include "Logging/logging.hpp"

#include <Windows.h>

H::hMessageBoxA::fn                  oMessageBoxA                = nullptr;
H::hVirtualAllocEx::fn               oVirtualAllocEx             = nullptr;
H::hWriteProccessMemory::fn          oWriteProccessMemory        = nullptr;

#define STRINGIFY_IMPL(s) #s
#define STRINGIFY(s)      STRINGIFY_IMPL(s)
#define PRINT_INTERFACE(name) L::ConsolePrint("%s: %s", STRINGIFY(name), name)

int WINAPI H::hMessageBoxA::Hooked(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
    L::ConsolePrint("-=hkMessageBoxW=-");
    PRINT_INTERFACE(lpText);
    PRINT_INTERFACE(lpCaption);
    L::ConsolePrint("-=-=-=-=-=-=-=-=\n");

    return oMessageBoxA(hWnd, "hooked", lpCaption, uType);
}

LPVOID WINAPI H::hVirtualAllocEx::Hooked(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    L::ConsolePrint("-=hkVirtualAllocEx=-");
    PRINT_INTERFACE(hProcess);
    PRINT_INTERFACE(lpAddress);
    PRINT_INTERFACE(dwSize);
    PRINT_INTERFACE(flAllocationType);
    PRINT_INTERFACE(flProtect);
    L::ConsolePrint("-=-=-=-=-=-=-=-=\n");

    return oVirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

bool WINAPI H::hWriteProccessMemory::Hooked(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten)
{
    L::ConsolePrint("-=hkWriteProccessMemory=-");
    PRINT_INTERFACE(hProcess);
    PRINT_INTERFACE(lpBaseAddress);
    PRINT_INTERFACE(lpBuffer);
    PRINT_INTERFACE(nSize);
    PRINT_INTERFACE(lpNumberOfBytesWritten);
    L::ConsolePrint("-=-=-=-=-=-=-=-=\n");

    return oWriteProccessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

void H::Initialize()
{
    MH_Initialize();
    MH_CreateHook(&MessageBoxA, &hMessageBoxA::Hooked, reinterpret_cast<LPVOID*>(&oMessageBoxA));
    MH_CreateHook(&VirtualAllocEx, &hVirtualAllocEx::Hooked, reinterpret_cast<LPVOID*>(&oVirtualAllocEx));
    MH_CreateHook(&WriteProcessMemory, &hWriteProccessMemory::Hooked, reinterpret_cast<LPVOID*>(&oWriteProccessMemory));

    MH_EnableHook(&MessageBoxA);
    MH_EnableHook(&VirtualAllocEx);
    MH_EnableHook(&WriteProcessMemory);
}

void H::Release()
{
    MH_Uninitialize();
}