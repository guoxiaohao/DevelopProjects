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
	BOOL InitAllData(int nPort, TCHAR* ExePath, TCHAR* XmlFile, LPVOID FuncAddress);//������ʼ��
	void StopExit();//�˳�����ֹ--�ȴ�Pad������ɺ���Ҫ�޸�
	int PortNum;
public:
	BOOL CreateUeProcess();//����Ŀ��UE����
	void GetUeSunPid();//��ȡ���߳�Pid
	void CloseUeAboutPro(DWORD &tPID);//�ر���Ҫ���̼��ͷ������Դ
	void CloseUeAboutPro1(DWORD &tPID);//�رմ��ڽ��̼��ͷ������Դ

	TCHAR SzUePath[255];
	HANDLE H_Ue;//������(������)���
	DWORD dwUePid;//������(������)pid
	DWORD dwUeSunPid;//�ӽ���pid
	HWND H_MainWnd;//UE�Ĵ��ھ��
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
	void PreRelease();//�ر�UE�Ĵ��ڼ����
public:
	void FindTargets(TCHAR* sz_Paths);//�����ļ���·������Ѱ�ļ������ļ�,�ȴ�Pad������ɺ���Ҫ�޸�
	void SetExePath(TCHAR* sz_Exe);//����Ŀ��UE��exe·��,�ȴ�Pad������ɺ���Ҫ�޸�
};

extern "C"
{
	MoniUe obj;

	GUOXHEXPORT BOOL InitAllData(int nPort, TCHAR* ExePath, TCHAR* XmlFile, LPVOID FuncAddress);
	GUOXHEXPORT void StopExit();//�˳�����ֹ,�ȴ�Pad������ɺ���Ҫ�޸�
	GUOXHEXPORT BOOL CreateUeProcess();//����Ŀ��UE����,�ȴ�Pad������ɺ���Ҫ�޸�
	GUOXHEXPORT void FindTargets(TCHAR* sz_Paths);//�����ļ���·������Ѱ�ļ������ļ�,�ȴ�Pad������ɺ���Ҫ�޸�
	GUOXHEXPORT void SetExePath(TCHAR* sz_Exe);//����Ŀ��UE��exe·��,�ȴ�Pad������ɺ���Ҫ�޸�
	GUOXHEXPORT void PreRelease();//�ر�UE�Ĵ��ڼ����

	GUOXHEXPORT BOOL SendDatas(TCHAR* Sz_DataSend);
}