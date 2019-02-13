#include "pch.h"
#include "CpuInfo.h"

#include "OlsApi.h"

int PerCpuValues;
DWORD WINAPI ThreadEveryCpuTemperature(LPVOID lps);

CCpuInfo::CCpuInfo()
{
	InitializeOls();

	lpThreadMain = nullptr;
	HEventMain = INVALID_HANDLE_VALUE;
	HEventSingle = INVALID_HANDLE_VALUE;

	H_NamePipeServer = INVALID_HANDLE_VALUE;

	HPipeWaitEvent = INVALID_HANDLE_VALUE;
	lpPipeWait = nullptr;

	HPipeRecvEvent = INVALID_HANDLE_VALUE;
	bThreadPipeRecv = TRUE;
	lpPipeRecv = nullptr;

	memset(szRecvInfos, 0, sizeof(szRecvInfos));
	memset(szSendInofs, 0, sizeof(szSendInofs));

	HWritesEvent = INVALID_HANDLE_VALUE;
	HMutexWrite = INVALID_HANDLE_VALUE;

	lpCpuInfos = nullptr;
	bCpuInfos = TRUE;
}

CCpuInfo::~CCpuInfo()
{
	EndSer();
	if (HPipeRecvEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(HPipeRecvEvent); HPipeRecvEvent = INVALID_HANDLE_VALUE;
	}
	if (HWritesEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(HWritesEvent); HWritesEvent = INVALID_HANDLE_VALUE;
	}
	if (HMutexWrite != INVALID_HANDLE_VALUE)
	{
		CloseHandle(HMutexWrite); HMutexWrite = INVALID_HANDLE_VALUE;
	}
	DeinitializeOls();
}

void CCpuInfo::StartSer()//服务主线程
{
	H_NamePipeServer = CreateNamedPipeA("\\\\.\\pipe\\SerExamplePipe", PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_BYTE, 1, 1024, 1024, 0, NULL);
	if (H_NamePipeServer == INVALID_HANDLE_VALUE)
	{
		//日志信息
		int nRet = GetLastError();
		TCHAR szMsg[255] = L"PipeSer Handle Wrong";
		m_logs.WriteLog(szMsg);
		return;
	}
	else
	{
		//日志信息
		TCHAR szMsg[255] = L"PipeSer Handle Right";
		m_logs.WriteLog(szMsg);
		lpPipeWait = new std::thread(&CCpuInfo::ThreadPipeWait, this);
		lpCpuInfos = new std::thread(&CCpuInfo::GetCpuTempe, this);
	}
	HEventMain = CreateEvent(NULL, TRUE, FALSE, NULL);
	WaitForSingleObject(HEventMain, INFINITE);
}

void CCpuInfo::EndSer()
{
	if (lpPipeWait != nullptr)
	{
		if (HPipeWaitEvent != INVALID_HANDLE_VALUE)
		{
			CloseHandle(HPipeWaitEvent); HPipeWaitEvent = INVALID_HANDLE_VALUE;
		}
		lpPipeWait->join();
		delete lpPipeWait; lpPipeWait = nullptr;
	}
	if (HPipeWaitEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(HPipeWaitEvent); HPipeWaitEvent = INVALID_HANDLE_VALUE;
	}

	if (bThreadPipeRecv&&lpPipeRecv != nullptr)
	{
		if (HEventSingle != INVALID_HANDLE_VALUE)
		{
			SetEvent(HEventSingle);
		}
		bThreadPipeRecv = FALSE;
		lpPipeRecv->join();
		delete lpPipeRecv; lpPipeRecv = nullptr;
	}
	if (HEventSingle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(HEventSingle); HEventSingle = INVALID_HANDLE_VALUE;
	}

	if (bCpuInfos&&lpCpuInfos!=nullptr)
	{
		bCpuInfos = FALSE;
		lpCpuInfos->join();
		delete lpCpuInfos; lpCpuInfos = nullptr;
	}

	if (H_NamePipeServer != INVALID_HANDLE_VALUE)
	{
		CloseHandle(H_NamePipeServer); H_NamePipeServer = INVALID_HANDLE_VALUE;
	}

	//释放主线程阻塞消息
	if (HEventMain != INVALID_HANDLE_VALUE)
	{
		SetEvent(HEventMain);
	}
}

void CCpuInfo::PauseSer()
{
	if (HEventSingle != INVALID_HANDLE_VALUE)
	{
		ResetEvent(HEventSingle);
	}
}

void CCpuInfo::ContinueSer()
{
	if (HEventSingle != INVALID_HANDLE_VALUE)
	{
		SetEvent(HEventSingle);
	}
}

void CCpuInfo::ThreadPipeWait()
{
	if (HPipeWaitEvent == INVALID_HANDLE_VALUE)
	{
		HPipeWaitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	memset(&overlapPipeWait, 0, sizeof(OVERLAPPED));
	overlapPipeWait.hEvent = HPipeWaitEvent;

	//日志信息
	TCHAR szMsg[255] = L"Waiting Pipe Connect";
	m_logs.WriteLog(szMsg);
	ConnectNamedPipe(H_NamePipeServer, &overlapPipeWait);
	//当有客户端进行连接时，事件变成有信号的状态
	int nRets = WaitForSingleObject(overlapPipeWait.hEvent, INFINITE);
	if (nRets == WAIT_OBJECT_0)
	{
		if (lpPipeRecv == nullptr)
		{
			lpPipeRecv = new std::thread(&CCpuInfo::ThreadPipeRecv, this);
		}
		else
		{
			lpPipeRecv->join();//已经return退出线程,顺手添加
			delete lpPipeRecv;  lpPipeRecv = nullptr;
			lpPipeRecv = new std::thread(&CCpuInfo::ThreadPipeRecv, this);
		}
		//日志信息
		TCHAR szMsg[255] = L"Pipe Connect Right";
		m_logs.WriteLog(szMsg);
	}
}

void CCpuInfo::ThreadPipeRecv()
{
	if (HPipeRecvEvent == INVALID_HANDLE_VALUE)
	{
		HPipeRecvEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	while (bThreadPipeRecv)
	{
		if (HEventSingle == INVALID_HANDLE_VALUE)
		{
			HEventSingle = CreateEvent(NULL, TRUE, TRUE, NULL);
		}
		WaitForSingleObject(HEventSingle, INFINITE);

		memset(&overlapPipeRecv, 0, sizeof(OVERLAPPED));
		overlapPipeRecv.hEvent = HPipeRecvEvent;
		memset(szRecvInfos, 0, sizeof(szRecvInfos));

		DWORD dwReadBytes = 0;
		ReadFile(H_NamePipeServer, szRecvInfos, 255, &dwReadBytes, &overlapPipeRecv);

		int nRets = WaitForSingleObject(overlapPipeRecv.hEvent, 200);
		if (nRets == WAIT_OBJECT_0)
		{
			DWORD dwReadDone;
			GetOverlappedResult(H_NamePipeServer, &overlapPipeRecv, &dwReadDone, TRUE);
			if (dwReadDone == 0)
			{
				if (lpPipeWait != nullptr)
				{
					lpPipeWait->join();
					delete lpPipeWait; lpPipeWait = nullptr;
				}
				if (H_NamePipeServer != INVALID_HANDLE_VALUE)
				{
					CloseHandle(H_NamePipeServer); H_NamePipeServer = INVALID_HANDLE_VALUE;
				}
				H_NamePipeServer = CreateNamedPipeA("\\\\.\\pipe\\SerExamplePipe", PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
					PIPE_TYPE_BYTE, 1, 1024, 1024, 0, NULL);
				if (H_NamePipeServer != INVALID_HANDLE_VALUE)
				{
					lpPipeWait = new std::thread(&CCpuInfo::ThreadPipeWait, this);
					return;
				}
			}
			else
			{
				if (strcmp(szRecvInfos, "NeedMessage") == 0)
				{
					SendDatas();
				}
			}
		}
		else
		{
			continue;
		}

	}
}

void CCpuInfo::SendDatas()
{
	if (HMutexWrite == INVALID_HANDLE_VALUE)
	{
		HMutexWrite = CreateMutex(NULL, FALSE, NULL);
	}
	if (HWritesEvent)
	{
		HWritesEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	WaitForSingleObject(HMutexWrite, INFINITE);
	memset(&overlapWrite, 0, sizeof(overlapWrite));
	overlapWrite.hEvent = HWritesEvent;
	DWORD dwWrite;
	WriteFile(H_NamePipeServer, szSendInofs, strlen(szSendInofs), &dwWrite, &overlapWrite);
	int nRets = WaitForSingleObject(overlapWrite.hEvent, 200);
	ReleaseMutex(HMutexWrite);
}

void CCpuInfo::GetCpuTempe()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	int nCpu = info.dwNumberOfProcessors;
	int *tValues = new int[nCpu];

	HANDLE H_Record = INVALID_HANDLE_VALUE;
	while (bCpuInfos)
	{
		Sleep(200);
		for (int i = 0; i < nCpu; i++)
		{
			H_Record = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadEveryCpuTemperature, (LPVOID)&PerCpuValues, CREATE_SUSPENDED, 0);
			SetThreadAffinityMask(H_Record, i + 1);
			ResumeThread(H_Record);
			WaitForSingleObject(H_Record, INFINITE);
			tValues[i] = PerCpuValues;
		}

		if (HMutexWrite == INVALID_HANDLE_VALUE)
		{
			HMutexWrite = CreateMutex(NULL, FALSE, NULL);
		}
		WaitForSingleObject(HMutexWrite, INFINITE);
		memset(szSendInofs, 0, sizeof(szSendInofs));
		for (int i = 0; i < nCpu; i++)
		{
			char SzVal1[10] = { 0 };
			sprintf_s(SzVal1, "%d_", tValues[i]);
			strcat_s(szSendInofs, SzVal1);
		}
		ReleaseMutex(HMutexWrite);
	}

	if (H_Record != nullptr)
	{
		CloseHandle(H_Record); H_Record = nullptr;
	}
	delete[]tValues;
	tValues = nullptr;
}

DWORD WINAPI ThreadEveryCpuTemperature(LPVOID lps)
{
	int *vals = (int*)lps;
	*vals = 0;

	DWORD index;
	index = 0x19c;
	DWORD eax, edx;
	if (RdmsrTx(index, &eax, &edx, 1))
	{
		DWORD dwVal = 100 - ((eax & 0x007f0000) >> 16);
		*vals = dwVal;
	}

	return 0;
}