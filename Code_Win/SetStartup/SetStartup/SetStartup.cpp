// SetStartup.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <io.h>

#include <string>

int main()
{
	TCHAR szDebug[255] = { 0 };
	TCHAR szFile[255] = { 0 };

	GetModuleFileNameW(NULL, szDebug, 255);
	std::wstring StrDebug = szDebug;
	int nPos = StrDebug.find_last_of('\\');
	if (nPos<=0)
	{
		std::cout << "Failed" << std::endl;
		return 1;
	}
	std::wstring StrFile = StrDebug.substr(0, nPos);
	StrFile = StrFile + L"\\" + L"Config.ini";
	wcscpy_s(szFile, StrFile.c_str());

	char szFileA[255] = { 0 };
	int nLen = WideCharToMultiByte(CP_ACP, 0, szFile, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, szFile, -1, szFileA, nLen, NULL, NULL);
	if (_access(szFileA, 0)!=0)
	{
		std::cout << "Failed" << std::endl;
		return 1;
	}

	TCHAR szSrc[255] = { 0 };
	TCHAR szDest[255] = { 0 };
	GetPrivateProfileStringW(L"FileInfo", L"Src", NULL, szSrc, 255, szFile);
	GetPrivateProfileStringW(L"FileInfo", L"Det", NULL, szDest, 255, szFile);

	HKEY hKey;
	int nRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szDest, 0, KEY_WRITE, &hKey);
	if (nRet == 0 )
	{
		nRet = RegSetValueEx(hKey, L"Deamon", 0, REG_SZ, (BYTE*)szSrc, 255);
		if (nRet!=0)
		{
			std::cout << "Failed" << std::endl;
		}
		RegCloseKey(hKey);
	}
	else
	{
		std::cout << "Failed" << std::endl;
		return 1;
	}

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
