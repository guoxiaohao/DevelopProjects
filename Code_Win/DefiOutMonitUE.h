#pragma once

#ifdef GUOXHAUTHORITY
#define GUOXHEXPORT _declspec(dllexport)
#else
#define GUOXHEXPORT _declspec(dllimport)
#endif

class MoniUe
{
public:
	MoniUe();
	~MoniUe();
public:
	BOOL InitAllData(int nPort, TCHAR* ExePath, TCHAR* XmlFile, LPVOID FuncAddress);//启动初始化
	void StopExit();//退出和终止--等待Pad开发完成后需要修改
	int PortNum;
public:
	BOOL CreateUeProcess();//启动目标UE进程
	void GetUeSunPid();//获取子线程Pid
	void CloseUeAboutPro(DWORD &tPID);//关闭主要进程及释放相关资源
	void CloseUeAboutPro1(DWORD &tPID);//关闭窗口进程及释放相关资源

	TCHAR SzUePath[255];
	HANDLE H_Ue;//主进程(父进程)句柄
	DWORD dwUePid;//主进程(父进程)pid
	DWORD dwUeSunPid;//子进程pid
	HWND H_MainWnd;//UE的窗口句柄
public:
	BOOL SendDatas(TCHAR* Sz_DataSend);
	HANDLE H_MutexWrite;
public:
	HANDLE H_EventCreateUe;
public:
	int nFps;
public:
	char SzXmlFile[255];
	void ReadXml();
public:
	void PreRelease();//关闭UE的窗口及句柄
public:
	void FindTargets(TCHAR* sz_Paths);//根据文件夹路径，找寻文件夹下文件,等待Pad开发完成后需要修改
	void SetExePath(TCHAR* sz_Exe);//设置目标UE的exe路径,等待Pad开发完成后需要修改
};

extern "C"
{
	MoniUe obj;

	GUOXHEXPORT BOOL InitAllData(int nPort, TCHAR* ExePath, TCHAR* XmlFile, LPVOID FuncAddress);
	GUOXHEXPORT void StopExit();//退出和终止,等待Pad开发完成后需要修改
	GUOXHEXPORT BOOL CreateUeProcess();//启动目标UE进程,等待Pad开发完成后需要修改
	GUOXHEXPORT void FindTargets(TCHAR* sz_Paths);//根据文件夹路径，找寻文件夹下文件,等待Pad开发完成后需要修改
	GUOXHEXPORT void SetExePath(TCHAR* sz_Exe);//设置目标UE的exe路径,等待Pad开发完成后需要修改
	GUOXHEXPORT void PreRelease();//关闭UE的窗口及句柄

	GUOXHEXPORT BOOL SendDatas(TCHAR* Sz_DataSend);
}