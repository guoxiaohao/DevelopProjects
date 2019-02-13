#pragma once



class CCpuInfo
{
public:
	CCpuInfo();
	~CCpuInfo();
public:
	std::thread* lpThreadMain;
	void StartSer();
	void EndSer();
	void PauseSer();
	void ContinueSer();
private:
	HANDLE HEventMain;
	HANDLE HEventSingle;
private:
	HANDLE H_NamePipeServer;
private:
	void ThreadPipeWait();
	OVERLAPPED overlapPipeWait;
	HANDLE HPipeWaitEvent;
	std::thread* lpPipeWait;
private:
	void ThreadPipeRecv();
	OVERLAPPED overlapPipeRecv;
	HANDLE HPipeRecvEvent;
	BOOL bThreadPipeRecv;
	std::thread* lpPipeRecv;
	char szRecvInfos[255];
private:
	void SendDatas();
	OVERLAPPED overlapWrite;
	HANDLE HWritesEvent;
	HANDLE HMutexWrite;
	char szSendInofs[255];
private:
	std::thread* lpCpuInfos;
	void GetCpuTempe();
	BOOL bCpuInfos;
};
