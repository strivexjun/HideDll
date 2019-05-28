// HideDLL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "XHideDll.h"


int main()
{
 	
	LoadLibrary(_T("C:\\Users\\iiqone\\Desktop\\123.dll"));

	XHideDll::PrintModuleList();

	XHideDll::HideInLoadOrderLinks(GetModuleHandle(_T("123.dll")));

	XHideDll::HideInMemoryOrderLinks(GetModuleHandle(_T("123.dll")));

	XHideDll::HideInInitializationOrderLinks(GetModuleHandle(_T("123.dll")));

	XHideDll::PrintModuleList();

	return 0;
}


