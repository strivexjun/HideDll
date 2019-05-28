//
//Author:Xjun
//

#pragma once

#include <tchar.h>
#include <windows.h>
#include <TlHelp32.h>
#include <intrin.h>

#include "ntdll/ntdll.h"

#ifndef _WIN64
#pragma comment(lib,"ntdll/ntdll_x86.lib")
#else
#pragma comment(lib,"ntdll/ntdll_x64.lib")
#endif

class XHideDll
{
public:
	XHideDll();
	~XHideDll();

	static PVOID GetProcessPEB();

	static VOID PrintModuleList();

	static BOOL HideInLoadOrderLinks(HMODULE dllBase);

	static BOOL HideInMemoryOrderLinks(HMODULE dllBase);

	static BOOL HideInInitializationOrderLinks(HMODULE dllBase);

};

