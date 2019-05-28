//
//Author:Xjun
//

//#include "stdafx.h"
#include "XHideDll.h"

XHideDll::XHideDll()
{
}

XHideDll::~XHideDll()
{
}

PVOID XHideDll::GetProcessPEB()
{
#ifdef _WIN64
	return (PVOID)__readgsqword(0x60);
#else
	return (PVOID)__readfsdword(0x30);
#endif
}

BOOL XHideDll::HideInLoadOrderLinks(HMODULE dllBase)
{
	BOOL r = FALSE;

	PPEB peb = (PPEB)GetProcessPEB();

	PLIST_ENTRY OrderModuleHead, OrderModuleTail;

	PLDR_DATA_TABLE_ENTRY pLdrDataEntry = NULL;

	OrderModuleHead = OrderModuleTail = peb->Ldr->InLoadOrderModuleList.Blink;

	do
	{
		pLdrDataEntry = (PLDR_DATA_TABLE_ENTRY)CONTAINING_RECORD(OrderModuleHead, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		if (pLdrDataEntry->DllBase == NULL)
		{
			break;
		}

		// 		_tprintf(_T("DLLBase:%p Size:%08X ShortName:%s FullName:%s\n\n"), pLdrDataEntry->DllBase, pLdrDataEntry->SizeOfImage,
		// 			pLdrDataEntry->BaseDllName.Buffer, pLdrDataEntry->FullDllName.Buffer);

		if (pLdrDataEntry->DllBase == dllBase)
		{
			RemoveEntryList(OrderModuleHead);
			r = TRUE;
		}

		OrderModuleHead = OrderModuleHead->Blink;

	} while (OrderModuleHead != OrderModuleTail);

	//	_tprintf(_T("--------------------------------------------------------------\n"));

	return r;

}

BOOL XHideDll::HideInMemoryOrderLinks(HMODULE dllBase)
{
	BOOL r = FALSE;

	PPEB peb = (PPEB)GetProcessPEB();

	PLIST_ENTRY OrderModuleHead, OrderModuleTail;

	PLDR_DATA_TABLE_ENTRY pLdrDataEntry = NULL;

	OrderModuleHead = OrderModuleTail = peb->Ldr->InMemoryOrderModuleList.Blink;

	do
	{
		pLdrDataEntry = (PLDR_DATA_TABLE_ENTRY)CONTAINING_RECORD(OrderModuleHead, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (pLdrDataEntry->DllBase == NULL)
		{
			break;
		}

		// 		_tprintf(_T("DLLBase:%p Size:%08X ShortName:%s FullName:%s\n\n"), pLdrDataEntry->DllBase, pLdrDataEntry->SizeOfImage,
		// 			pLdrDataEntry->BaseDllName.Buffer, pLdrDataEntry->FullDllName.Buffer);

		if (pLdrDataEntry->DllBase == dllBase)
		{
			RemoveEntryList(OrderModuleHead);
			r = TRUE;
		}

		OrderModuleHead = OrderModuleHead->Blink;

	} while (OrderModuleHead != OrderModuleTail);

	//	_tprintf(_T("--------------------------------------------------------------\n"));

	return r;

}

BOOL XHideDll::HideInInitializationOrderLinks(HMODULE dllBase)
{
	BOOL r = FALSE;

	PPEB peb = (PPEB)GetProcessPEB();

	PLIST_ENTRY OrderModuleHead, OrderModuleTail;

	PLDR_DATA_TABLE_ENTRY pLdrDataEntry = NULL;

	OrderModuleHead = OrderModuleTail = peb->Ldr->InInitializationOrderModuleList.Blink;

	do
	{
		pLdrDataEntry = (PLDR_DATA_TABLE_ENTRY)CONTAINING_RECORD(OrderModuleHead, LDR_DATA_TABLE_ENTRY, InInitializationOrderLinks);

		if (pLdrDataEntry->DllBase == NULL)
		{
			break;
		}

		// 		_tprintf(_T("DLLBase:%p Size:%08X ShortName:%s FullName:%s\n\n"), pLdrDataEntry->DllBase, pLdrDataEntry->SizeOfImage,
		// 			pLdrDataEntry->BaseDllName.Buffer, pLdrDataEntry->FullDllName.Buffer);

		if (pLdrDataEntry->DllBase == dllBase)
		{
			RemoveEntryList(OrderModuleHead);
			r = TRUE;
		}

		OrderModuleHead = OrderModuleHead->Blink;

	} while (OrderModuleHead != OrderModuleTail);

	//
	_tprintf(_T("--------------------------------------------------------------\n"));

	return r;

}

VOID XHideDll::PrintModuleList()
{
	HANDLE hSnaphot;
	MODULEENTRY32 md32 = { 0 };
	BOOL exist;

	md32.dwSize = sizeof(md32);

	hSnaphot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());

	exist = Module32First(hSnaphot, &md32);

	while (exist)
	{
		_tprintf(_T("%s\n"), md32.szModule);
		exist = Module32Next(hSnaphot, &md32);
	}

	CloseHandle(hSnaphot);

	_tprintf(_T("--------------------------------------------"));
}