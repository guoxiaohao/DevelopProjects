// SerExample.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"



TCHAR Sz_ServerName[255] = L"SerExample";//服务名
void WINAPI MyServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);//服务主函数
void WINAPI MyServiceHandler(DWORD dwControl);//服务控制程序

SERVICE_STATUS_HANDLE ServiceStatusHandle = nullptr;
SERVICE_STATUS ServiceStatus;

CLogSys m_logs;
CCpuInfo m_cpuInfos;

int main()
{
	//服务运行
	//服务线程入口
	m_logs.FuncBegin();

	SERVICE_TABLE_ENTRY ServiceTable[] =
	{
		{ Sz_ServerName, MyServiceMain },
		{ NULL, NULL }
	};

	//连接到服务控制管理器
	TCHAR szMsgs[255] = L"Ser Entry";
	m_logs.WriteLog(szMsgs);
	StartServiceCtrlDispatcher(ServiceTable);

	return 0;
}

void WINAPI MyServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)//服务控制程序
{
	ServiceStatusHandle = RegisterServiceCtrlHandler(Sz_ServerName, MyServiceHandler);

	ServiceStatus.dwServiceType = SERVICE_WIN32;//表示该服务私有
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING; //初始化服务，正在开始
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;//服务可以接受的请求，这里我们只接受停止服务请求和暂停恢复请求
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	//必须调用SetServiceStatus()来响应服务控制程序的每次请求通知
	SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

	//开始运行服务
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

	m_cpuInfos.StartSer();
	if (m_cpuInfos.lpThreadMain != nullptr)
	{
		m_cpuInfos.lpThreadMain->join();
		if (m_cpuInfos.lpThreadMain != nullptr)
		{
			delete m_cpuInfos.lpThreadMain; m_cpuInfos.lpThreadMain = nullptr;
		}
	}

	TCHAR szMsgs[255] = L"Ser Leave";
	m_logs.WriteLog(szMsgs);
}

void WINAPI MyServiceHandler(DWORD dwControl)//服务主函数
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP://请求终止服务
		{
		TCHAR szMsgs[255] = L"REQ-STOP";
		m_logs.WriteLog(szMsgs);
		m_cpuInfos.EndSer();

		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOP;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
		}
		break;
	case SERVICE_CONTROL_PAUSE:
		{
		TCHAR szMsgs[255] = L"REQ-PAUSE";
		m_logs.WriteLog(szMsgs);
		m_cpuInfos.PauseSer();

		ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
		}
		break;
	case SERVICE_CONTROL_CONTINUE:
		{
		TCHAR szMsgs[255] = L"REQ-CONTINUE";
		m_logs.WriteLog(szMsgs);
		m_cpuInfos.ContinueSer();

		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		SetServiceStatus(ServiceStatusHandle, &ServiceStatus);
		}
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		{
		TCHAR szMsgs[255] = L"REQ-SHUTDOWN";
		m_logs.WriteLog(szMsgs);
		m_cpuInfos.EndSer();

		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(ServiceStatusHandle, &ServiceStatus);//报告服务运行状态 
		}
		break;
	default:
		break;
	}
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
