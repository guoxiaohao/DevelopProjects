#include "stdafx.h"
#include "DefiOutMonitUE.h"

#include "PreError.h"
#include "tinyxml.h"
#include <io.h>

SOCKET ListenSocket = INVALID_SOCKET;
SOCKADDR_IN addrRecv;

LPWSAOVERLAPPEDStru OverLapVar = nullptr;
WSAEVENT H_WasEvent = nullptr;

HANDLE H_Listen = nullptr;
HANDLE H_Recv = nullptr;
HANDLE H_Heart = nullptr;
HANDLE H_Result = nullptr;

BOOL bListen = TRUE;
BOOL bRecv = TRUE;
BOOL bHeart = TRUE;
int nHeart = 0;
int nSignalRet = -1;

bool bLink = false;

DWORD WINAPI ThreadUseListen(LPVOID lp);
DWORD WINAPI ThreadUseRecv(LPVOID lp);
DWORD WINAPI ThreadUseHeart(LPVOID lp);
DWORD WINAPI ThreadResult(LPVOID lp);

TiXmlDocument docXml;
std::map<std::string, ErrorStruct> mapErrors;

DWORD WINAPI ThreadMonitorUERunning(LPVOID lp);
DWORD WINAPI ThreadMonitorUEFore(LPVOID lp);
HANDLE H_UECrash = nullptr;
HANDLE H_UEFore = nullptr;
BOOL bUECrash = TRUE;
BOOL bUEFore = TRUE;

ErrorStruct NewStructsAccordInfos(char* szInfos, TCHAR* szDetail);
//往消息队列中放入异常消息
typedef void(*pCallBackFun)(int nPrioValue, int nTargValue, TCHAR* Sz_Content, TCHAR* Sz_Detail);
pCallBackFun pFunAddress = nullptr;
BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);//回调函数-查找进程主窗口

MoniUe::MoniUe()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&addrRecv, 0, sizeof(SOCKADDR_IN));

	wmemset(SzUePath, L'\0', sizeof(SzUePath)/sizeof(TCHAR));
	PortNum = 0;
	H_Ue = nullptr;
	dwUePid = 0;
	dwUeSunPid = 0;
	H_MainWnd = nullptr;

	nFps = 0;

	H_MutexWrite = CreateMutex(NULL, FALSE, NULL);
	H_EventCreateUe = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void MoniUe::PreRelease()
{
	if (bUECrash&&H_UECrash != nullptr)
	{
		bUECrash = FALSE;
		WaitForSingleObject(H_UECrash, INFINITE);
		CloseHandle(H_UECrash); H_UECrash = nullptr;
	}

	if (bUEFore&&H_UEFore != nullptr)
	{
		bUEFore = FALSE;
		WaitForSingleObject(H_UEFore, INFINITE);
		CloseHandle(H_UEFore); H_UEFore = nullptr;
	}

	if (bHeart&&H_Heart != nullptr)
	{
		bHeart = FALSE;
		WaitForSingleObject(H_Heart, INFINITE);
		CloseHandle(H_Heart); H_Heart = nullptr;
	}

	if (bRecv&&H_Recv != nullptr)
	{
		bRecv = FALSE;
		WaitForSingleObject(H_Recv, INFINITE);
		CloseHandle(H_Recv); H_Recv = nullptr;
	}
	if (OverLapVar != nullptr)
	{
		closesocket(OverLapVar->socketUse);
		WSACloseEvent(H_WasEvent);
		H_WasEvent = nullptr;
		HeapFree(GetProcessHeap(), 0, OverLapVar);
		OverLapVar = nullptr;
	}

	if (bListen&&H_Listen != nullptr)
	{
		bListen = FALSE;
		closesocket(ListenSocket); ListenSocket = INVALID_SOCKET;
		WaitForSingleObject(H_Listen, INFINITE);
		CloseHandle(H_Listen); H_Listen = nullptr;
	}
}

MoniUe::~MoniUe()
{
	PreRelease();

	SetEvent(H_EventCreateUe);
	CloseHandle(H_EventCreateUe); H_EventCreateUe = nullptr;

	CloseHandle(H_MutexWrite); H_MutexWrite = nullptr;

	if (dwUeSunPid!=0)
	{
		CloseUeAboutPro1(dwUeSunPid);
	}
	if (H_MainWnd != nullptr)
	{
		H_MainWnd = nullptr;
	}

	if (H_Ue != nullptr)
	{
		DWORD Code_Exit;
		GetExitCodeProcess(H_Ue, &Code_Exit);
		if (Code_Exit == STILL_ACTIVE)//关闭创建的进程
		{
			DWORD nProcessID = GetProcessId(H_Ue);
			CloseUeAboutPro(nProcessID);
		}
		CloseHandle(H_Ue); H_Ue = nullptr;
	}
	WSACleanup();
}

BOOL MoniUe::InitAllData(int nPort, TCHAR* ExePath, TCHAR* XmlFile, LPVOID FuncAddress)
{
	pFunAddress = (pCallBackFun)FuncAddress;
	memset(SzXmlFile, '\0', sizeof(SzXmlFile));
	int nLen = WideCharToMultiByte(CP_ACP, 0, XmlFile, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, XmlFile, -1, SzXmlFile, nLen, NULL, NULL);
	ReadXml();
	PortNum = nPort;
	wmemcpy(SzUePath, ExePath, wcslen(ExePath));
	char Sz_ExePath[255] = { 0 };

	int Num = WideCharToMultiByte(CP_OEMCP, NULL, ExePath, -1, NULL, 0, NULL, FALSE);
	WideCharToMultiByte(CP_OEMCP, NULL, ExePath, -1, Sz_ExePath, Num, NULL, FALSE);

	if (_access(Sz_ExePath, 0) != 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void MoniUe::StopExit()
{

}

void MoniUe::ReadXml()
{
	//xml文件操作
	docXml.LoadFile(SzXmlFile);
	TiXmlElement* lpElemRoot = docXml.RootElement();
	//开始获取xml中数据
	//Part1
	TiXmlElement* lpPartSer = lpElemRoot->FirstChildElement("Part");
	while (lpPartSer!=nullptr&&strcmp("UECONTENT", lpPartSer->Attribute("Name")) != 0)
	{
		lpPartSer = lpPartSer->NextSiblingElement();
	}
	if (lpPartSer== nullptr)
	{
		return;
	}

	TiXmlElement* lpPartSerChild = lpPartSer->FirstChildElement();

	while (lpPartSerChild != nullptr)
	{
		std::string mapKey = lpPartSerChild->Attribute("Name");

		char szPrio[255] = { 0 };
		char szTarget[255] = { 0 };
		char szCont[255] = { 0 };
		TCHAR szContW[255] = { 0 };

		strcpy(szPrio, lpPartSerChild->Attribute("Prio"));
		strcpy(szTarget, lpPartSerChild->Attribute("Target"));
		strcpy(szCont, lpPartSerChild->GetText());
		int Lens = MultiByteToWideChar(CP_ACP, 0, szCont, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, szCont, -1, szContW, Lens);

		ErrorStruct errInfo;
		errInfo.nPrio = atoi(szPrio);
		errInfo.nTarget = atoi(szTarget);
		wcscpy(errInfo.szContents, szContW);

		mapErrors.insert(std::pair<std::string, ErrorStruct>(mapKey, errInfo));

		lpPartSerChild = lpPartSerChild->NextSiblingElement();
	}
}

/*******启动或关闭UE进程*********/
BOOL MoniUe::CreateUeProcess()
{
	STARTUPINFO startinfo;
	ZeroMemory(&startinfo, sizeof(startinfo));
	startinfo.cb = sizeof(startinfo);

	PROCESS_INFORMATION proinfo;
	ZeroMemory(&proinfo, sizeof(proinfo));

	std::map<std::string, ErrorStruct>::iterator  iter;
	//创建进程
	BOOL nFlag1 = CreateProcess(SzUePath,
		NULL,
		NULL,	//lpProcessAttributes process info
		NULL,	//lpThreadAttributes thread info
		FALSE,	//inheritable
		0,		//creation flags
		NULL,	//environment  
		NULL,	//current directory
		&startinfo,
		&proinfo);
	if (!nFlag1)
	{
		return nFlag1;
	}

	//获得子进程PID
	nFlag1 = FALSE;
	H_Ue = proinfo.hProcess;
	dwUePid = GetProcessId(H_Ue);
	for (int i = 0; i < 100; i++)
	{
		Sleep(6000);
		GetUeSunPid();
		if (dwUeSunPid!=0)
		{
			nFlag1 = TRUE;
			break;
		}
	}
	if (!nFlag1)
	{
		return FALSE;
	}

	//获得子进程窗口句柄
	EnumFunArg EnumWin;
	EnumWin.dwProcessId = dwUeSunPid;
	EnumWin.hWnd = nullptr;
	EnumWindows(EnumWindowCallBack, (LPARAM)&EnumWin);
	H_MainWnd = EnumWin.hWnd;
	if (H_MainWnd == nullptr)
	{
		return FALSE;
	}
	
	H_Listen = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadUseListen, (LPVOID)this, 0, NULL);
	H_Recv = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadUseRecv, (LPVOID)this, 0, NULL);
	H_Result = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadResult, (LPVOID)this, 0, NULL);

	WaitForSingleObject(H_Result, INFINITE);
	DWORD dwRet = 0;
	GetExitCodeThread(H_Result, &dwRet);

	if (dwRet==66)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void MoniUe::CloseUeAboutPro(DWORD &tPID)
{
	HANDLE hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, tPID);
	TerminateProcess(hProcessHandle, 4);
	CloseHandle(hProcessHandle); hProcessHandle = nullptr;
}

void MoniUe::CloseUeAboutPro1(DWORD &tPID)
{
	HANDLE hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, tPID);

	if (hProcessHandle != INVALID_HANDLE_VALUE)
	{
		DWORD Code_Exit;
		GetExitCodeProcess(hProcessHandle, &Code_Exit);

		if (Code_Exit == STILL_ACTIVE)
		{
			TerminateProcess(hProcessHandle, 4);
		}
		CloseHandle(hProcessHandle); hProcessHandle = nullptr;
	}
}

void MoniUe::GetUeSunPid()
{
	PROCESSENTRY32 ProInfo;
	ProInfo.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hp, &ProInfo))
	{
		do
		{
			if (ProInfo.th32ParentProcessID == dwUePid)//UE为父进程,开辟子进程
			{
				dwUeSunPid = ProInfo.th32ProcessID;
			}
		} while (Process32Next(hp, &ProInfo));
	}
}

BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);

	EnumFunArg* Lp_Used = (EnumFunArg*)lParam;

	if (dwProcessId == Lp_Used->dwProcessId && IsWindowVisible(hWnd) == TRUE)
	{
		Lp_Used->hWnd = hWnd;
		return FALSE;
	}

	return TRUE;
}

BOOL MoniUe::SendDatas(TCHAR* Sz_DataSend)
{
	if (!bLink)
	{
		return FALSE;
	}

	BOOL bRet;
	WaitForSingleObject(H_MutexWrite, INFINITE);

	char Sz_Trans[255] = { 0 };
	int Num = WideCharToMultiByte(CP_OEMCP, NULL, Sz_DataSend, -1, NULL, 0, NULL, FALSE);
	WideCharToMultiByte(CP_OEMCP, NULL, Sz_DataSend, -1, Sz_Trans, Num, NULL, FALSE);
	strcat(Sz_Trans, "%");
	bRet = send(OverLapVar->socketUse, Sz_Trans, strlen(Sz_Trans), 0);

	ReleaseMutex(H_MutexWrite);
	
	return bRet;
}

DWORD WINAPI ThreadUseListen(LPVOID lp)
{
	MoniUe* lp_used = nullptr;
	lp_used = (MoniUe*)lp;
	if (lp_used==nullptr)
	{
		return 1;
	}

	//与UE的TCP通信初始化
	addrRecv.sin_family = AF_INET;
	addrRecv.sin_port = htons(lp_used->PortNum);
	addrRecv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	bind(ListenSocket, (SOCKADDR*)&addrRecv, sizeof(SOCKADDR_IN));
	listen(ListenSocket, 5);

	while (bListen)
	{
		int nLen = sizeof(SOCKADDR);
		SOCKADDR_IN addRec;
		SOCKET socketTmp = accept(ListenSocket, (SOCKADDR*)&addRec, &nLen);

		if (socketTmp != INVALID_SOCKET)
		{
			H_WasEvent = WSACreateEvent();
			OverLapVar = (LPWSAOVERLAPPEDStru)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WSAOVERLAPPEDStru));

			OverLapVar->overlap.hEvent = H_WasEvent;
			OverLapVar->Buffer.len = 255;
			OverLapVar->Buffer.buf = OverLapVar->szMessage;
			OverLapVar->socketUse = socketTmp;

			WSARecv(OverLapVar->socketUse,
				&OverLapVar->Buffer, 1,
				&OverLapVar->NumberOfBytesRecvd,
				&OverLapVar->Flags,
				&OverLapVar->overlap,
				NULL);
		}
	}

	return 0;
}

DWORD WINAPI ThreadUseRecv(LPVOID lp)
{
	MoniUe* lp_used = nullptr;
	lp_used = (MoniUe*)lp;
	if (lp_used == nullptr)
	{
		return 1;
	}

	int nRet, nIndex;
	DWORD dwTransBytes;

	std::map<std::string, ErrorStruct>::iterator  iter;
	while (bRecv)
	{
		nRet = WSAWaitForMultipleEvents(1, &H_WasEvent, FALSE,
			500, FALSE);

		if (nRet == WSA_WAIT_FAILED || nRet == WSA_WAIT_TIMEOUT)
		{
			continue;
		}

		WSAGetOverlappedResult(OverLapVar->socketUse, &OverLapVar->overlap,
			&dwTransBytes, TRUE, &OverLapVar->Flags);

		//通信链路中断
		if (dwTransBytes == 0)
		{
			bHeart = FALSE;
			WaitForSingleObject(H_Heart, INFINITE);
			closesocket(OverLapVar->socketUse);
			WSACloseEvent(H_WasEvent); 
			H_WasEvent = nullptr;
			HeapFree(GetProcessHeap(), 0, OverLapVar);
			OverLapVar = nullptr;
			bLink = false;

			if (pFunAddress != nullptr)
			{
				iter = mapErrors.find("error_uecrash");
				ErrorStruct errValues = iter->second;

				pFunAddress(errValues.nPrio, errValues.nTarget, errValues.szContents, L"Ue Crash");
			}
		}
		else
		{
			//接收到的字符数据
			std::string Str_Recev = OverLapVar->szMessage;

			int nPos = Str_Recev.find_first_of('%');
			while (nPos != -1)
			{
				std::string Str_Sub = Str_Recev.substr(0, nPos);

				if (strcmp(Str_Sub.c_str(), "ue_request_connect") == 0)//接收UE链接请求
				{
					if (!bLink)
					{
						InterlockedExchange((LPLONG)&bLink, true);
						lp_used->SendDatas(L"ue_connect_success");
						bHeart = TRUE;
						H_Heart = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadUseHeart, lp, 0, NULL);
					}
				}
				if (strcmp(Str_Sub.c_str(), "ue_heart") == 0)//接收UE心跳
				{
					InterlockedExchange((LPLONG)&nHeart, 0);
				}
				if (strcmp(Str_Sub.c_str(), "right_uestartup") == 0)//启动UE成功
				{
					nSignalRet = 0;
					SetEvent(lp_used->H_EventCreateUe);
					H_UECrash = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadMonitorUERunning, (LPVOID)lp_used, 0, NULL);
					H_UEFore = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadMonitorUEFore, (LPVOID)lp_used, 0, NULL);
				}
				if (strcmp(Str_Sub.c_str(), "error_fps") == 0)//UE帧率过低
				{
					ErrorStruct errValues = NewStructsAccordInfos("error_fps", L"Ue FPS Wrong");
					pFunAddress(errValues.nPrio, errValues.nTarget, errValues.szContents, errValues.szDetails);
				}
				if (strcmp(Str_Sub.c_str(), "right_fps") == 0)//UE帧率恢复正常
				{
					ErrorStruct errValues = NewStructsAccordInfos("right_fps", L"Ue FPS Right");
					pFunAddress(errValues.nPrio, errValues.nTarget, errValues.szContents, errValues.szDetails);
				}

				Str_Recev = Str_Recev.substr(nPos + 1, Str_Recev.length() - nPos - 1);
				nPos = Str_Recev.find_first_of('%');
			}

			//更新重新接收
			dwTransBytes = 0;
			
			SOCKET tempsocket = OverLapVar->socketUse;
			memset(OverLapVar, 0, sizeof(WSAOVERLAPPEDStru));

			OverLapVar->overlap.hEvent = H_WasEvent;
			OverLapVar->Buffer.len = 255;
			OverLapVar->Buffer.buf = OverLapVar->szMessage;
			OverLapVar->socketUse = tempsocket;

			WSARecv(OverLapVar->socketUse,
				&OverLapVar->Buffer, 1,
				&OverLapVar->NumberOfBytesRecvd,
				&OverLapVar->Flags,
				&OverLapVar->overlap,
				NULL);
		}
	}

	return 0;
}

DWORD WINAPI ThreadUseHeart(LPVOID lp)
{
	MoniUe* lp_used = nullptr;
	lp_used = (MoniUe*)lp;
	if (lp_used == nullptr)
	{
		return 1;
	}

	while (bHeart)
	{
		Sleep(500);

		if (nHeart == 5)
		{
			continue;
		}
		InterlockedIncrement((LPLONG)&nHeart);

		if (nHeart == 5)
		{
			//心跳断开,等同于UE崩溃,需要重新启动UE
			if (pFunAddress != nullptr)
			{
				ErrorStruct errValues = NewStructsAccordInfos("error_uecrash", L"Ue Crash");
				pFunAddress(errValues.nPrio, errValues.nTarget, errValues.szContents, errValues.szDetails);
			}
		}

		lp_used->SendDatas(L"ue_heart");
	}

	return 0;
}

DWORD WINAPI ThreadResult(LPVOID lp)
{
	MoniUe* lp_used = nullptr;
	lp_used = (MoniUe*)lp;
	if (lp_used == nullptr)
	{
		return 1;
	}

	int nStatus = WaitForSingleObject(lp_used->H_EventCreateUe, 60000);
	if (nStatus == 0)
	{
		if (nSignalRet==0)
		{
			//抛出成功
			return 66;
		}
		else
		{
			//抛出错误
			return 1;
		}
	}
	else
	{
		//抛出错误
		return 1;
	}

	return 0;
}

DWORD WINAPI ThreadMonitorUERunning(LPVOID lp)
{
	/*MoniUe* lp_used = nullptr;
	lp_used = (MoniUe*)lp;
	if (lp_used==nullptr)
	{
		return 1;
	}

	while (bUECrash)
	{
		Sleep(200);
		if (!IsWindowEnabled(lp_used->H_MainWnd))
		{
			if (pFunAddress != nullptr)
			{
				ErrorStruct errValues = NewStructsAccordInfos("error_uecrash", L"Ue Crash");
				pFunAddress(errValues.nPrio, errValues.nTarget, errValues.szContents, errValues.szDetails);
				return 1;
			}
		}
	}*/

	return 0;
}

DWORD WINAPI ThreadMonitorUEFore(LPVOID lp)
{
	/*MoniUe* lp_used = nullptr;
	lp_used = (MoniUe*)lp;
	if (lp_used == nullptr)
	{
		return 1;
	}

	while (bUEFore)
	{
		Sleep(200);
		HWND H_Fore = GetForegroundWindow();
		HWND H_MyWind = lp_used->H_MainWnd;

		if (H_Fore != H_MyWind && IsWindowEnabled(H_MyWind))
		{
			if (!SetForegroundWindow(H_MyWind))
			{
				ErrorStruct errValues = NewStructsAccordInfos("error_uefront", L"Ue Not Front");
				pFunAddress(errValues.nPrio, errValues.nTarget, errValues.szContents, errValues.szDetails);
				return 1;
			}
		}
	}*/

	return 0;
}

void MoniUe::FindTargets(TCHAR* sz_Paths)
{

}

void MoniUe::SetExePath(TCHAR* sz_Exe)
{

}

ErrorStruct NewStructsAccordInfos(char* szInfos, TCHAR* szDetail)
{
	ErrorStruct errValues;
	std::map<std::string, ErrorStruct>::iterator  iter;
	iter = mapErrors.find(szInfos);

	if (iter!= mapErrors.end())
	{
		errValues = iter->second;
		wmemset(errValues.szDetails, L'\0', sizeof(errValues.szDetails) / sizeof(TCHAR));
		wcscpy(errValues.szDetails, szDetail);
	}

	return errValues;
}


/********外部接口*******/
BOOL InitAllData(int nPort, TCHAR* ExePath, TCHAR* XmlFile, LPVOID FuncAddress)
{
	return obj.InitAllData(nPort, ExePath, XmlFile, FuncAddress);
}

void StopExit()//退出和终止,等待Pad开发完成后需要修改
{
	obj.StopExit();
}

BOOL CreateUeProcess()//启动目标UE进程,等待Pad开发完成后需要修改
{
	return obj.CreateUeProcess();
}

void FindTargets(TCHAR* sz_Paths)//根据文件夹路径，找寻文件夹下文件,等待Pad开发完成后需要修改
{
	obj.FindTargets(sz_Paths);
}

void SetExePath(TCHAR* sz_Exe)//设置目标UE的exe路径,等待Pad开发完成后需要修改
{
	obj.SetExePath(sz_Exe);
}

void PreRelease()
{
	obj.PreRelease();
}



BOOL SendDatas(TCHAR* Sz_DataSend)
{
	return obj.SendDatas(Sz_DataSend);
}