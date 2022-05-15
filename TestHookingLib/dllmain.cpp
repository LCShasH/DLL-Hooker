#include <Windows.h>
#include <stdio.h>
#include <string>

#include "ext/MinHook/MinHook.h"
#include "Logging/logging.hpp"
#include "hooks.hpp"

bool g_Unload = false;

DWORD WINAPI OnDllAttach(LPVOID base)
{
    L::AttachConsole();
    H::Initialize();
    L::ConsolePrint("Hooks init!");
    while (!g_Unload)
    {
        if (GetAsyncKeyState(VK_END) & 1)
            g_Unload = true;
    }
    H::Release();

    FreeLibraryAndExitThread(static_cast<HMODULE>(base), 0);
    return TRUE;
}

BOOL WINAPI OnDllDetach()
{
    H::Release();
    L::DetachConsole();
    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, OnDllAttach, hModule, 0, nullptr);
        return TRUE;
    case DLL_PROCESS_DETACH:
        if (lpReserved == nullptr)
            return OnDllDetach();
        return TRUE;
    }
    return TRUE;
}

