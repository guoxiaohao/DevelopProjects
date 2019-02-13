#pragma once

#include <fstream>
#include <mutex>

class CLogSys
{
public:
	CLogSys(TCHAR* Sz_File);
	CLogSys(char* Sz_File);
	CLogSys();
	virtual ~CLogSys();
public:
	void WriteLog(TCHAR* Sz_OutPut);
	void WrtieLogA(char* Sz_OutPut);
	void WriteLogArray(TCHAR* Sz_Time, TCHAR* Sz_Content, TCHAR* Sz_Detail);
public:
	void FuncBegin();
	void FuncEnd();
private:
	TCHAR Sz_FileName_[255];
	std::mutex g_mutex_;
	std::wofstream LogWrite_;
};
