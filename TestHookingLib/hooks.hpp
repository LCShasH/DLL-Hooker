#pragma once

#include "ext/MinHook/MinHook.h"
#include <string>
#include <Windows.h>

namespace H 
{
	void Initialize();
	void Release();

	namespace hMessageBoxA {
		using fn = int(WINAPI*)(HWND, LPCSTR, LPCSTR, UINT);
		int WINAPI Hooked(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
	};

	namespace hVirtualAllocEx {
		using fn = LPVOID(WINAPI*)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
		LPVOID WINAPI Hooked(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
	};

	namespace hWriteProccessMemory {
		using fn = BOOL(WINAPI*)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*);
		bool WINAPI Hooked(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten);
	};
}