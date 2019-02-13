#include "pch.h"
#include "LogSys.h"

#include <atltime.h>

CLogSys::CLogSys()
{
	wmemset(Sz_FileName_, L'\0', sizeof(Sz_FileName_) / sizeof(TCHAR));
	
	TCHAR Sz_Temp[255] = { 0 };
	GetModuleFileNameW(NULL, Sz_Temp, 255);
	std::wstring Str_Temp = Sz_Temp;
	size_t nPos = Str_Temp.find_last_of('\\');
	Str_Temp = Str_Temp.substr(0, nPos);
	Str_Temp = Str_Temp + L"\\" + L"SerLog.txt";
	wcscpy_s(Sz_FileName_, Str_Temp.c_str());
}

CLogSys::CLogSys(TCHAR* Sz_File)
{
	wmemset(Sz_FileName_, L'\0', sizeof(Sz_FileName_) / sizeof(TCHAR));

	TCHAR Sz_Temp[255] = { 0 };
	GetModuleFileNameW(NULL, Sz_Temp, 255);
	std::wstring Str_Temp = Sz_Temp;
	size_t nPos = Str_Temp.find_last_of('\\');
	Str_Temp = Str_Temp.substr(0, nPos);
	Str_Temp = Str_Temp + L"\\" + Sz_File;
	wcscpy_s(Sz_FileName_, Str_Temp.c_str());
}

CLogSys::CLogSys(char* Sz_File)
{
	TCHAR szName[255] = { 0 };
	size_t nLen = MultiByteToWideChar(CP_ACP, 0, Sz_File, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Sz_File, -1, szName, nLen);

	wmemset(Sz_FileName_, L'\0', sizeof(Sz_FileName_) / sizeof(TCHAR));

	TCHAR Sz_Temp[255] = { 0 };
	GetModuleFileNameW(NULL, Sz_Temp, 255);
	std::wstring Str_Temp = Sz_Temp;
	size_t nPos = Str_Temp.find_last_of('\\');
	Str_Temp = Str_Temp.substr(0, nPos);
	Str_Temp = Str_Temp + L"\\" + szName;
	wcscpy_s(Sz_FileName_, Str_Temp.c_str());
}

CLogSys::~CLogSys()
{
	std::lock_guard<std::mutex> LockCriti(g_mutex_);
	wmemset(Sz_FileName_, L'\0', sizeof(Sz_FileName_) / sizeof(TCHAR));
}

void CLogSys::FuncBegin()
{

}

void CLogSys::FuncEnd()
{
	std::lock_guard<std::mutex> LockCriti(g_mutex_);
	wmemset(Sz_FileName_, L'\0', sizeof(Sz_FileName_) / sizeof(TCHAR));
}

void CLogSys::WriteLog(TCHAR* Sz_OutPut)
{
	std::lock_guard<std::mutex> lockCriti(g_mutex_);
	if (wcslen(Sz_FileName_) != 0)
	{
		CTime Time_Current;
		Time_Current = CTime::GetCurrentTime();
		int nYear = Time_Current.GetYear();
		int nMonth = Time_Current.GetMonth();
		int nDay = Time_Current.GetDay();
		int nHour = Time_Current.GetHour();
		int nMinute = Time_Current.GetMinute();
		int nSecond = Time_Current.GetSecond();

		TCHAR Sz_TimeCopy[255] = { 0 };
		wsprintf(Sz_TimeCopy, L"%04d:%02d:%02d-%02d::%02d::%02d----%s", nYear, nMonth, nDay, nHour, nMinute, nSecond, Sz_OutPut);
		LogWrite_.open(Sz_FileName_, std::ios::out | std::ios::ate | std::ios::app);
		if (LogWrite_.is_open())
		{
			LogWrite_ << Sz_TimeCopy << "\n";

			LogWrite_.close();
		}
	}
}

void CLogSys::WrtieLogA(char* Sz_OutPut)
{
	TCHAR Sz_Transfer[255] = { 0 };

	size_t nLen = MultiByteToWideChar(CP_ACP, 0, Sz_OutPut, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Sz_OutPut, -1, Sz_Transfer, nLen);
	WriteLog(Sz_Transfer);
}

void CLogSys::WriteLogArray(TCHAR* Sz_Time, TCHAR* Sz_Content, TCHAR* Sz_Detail)
{
	std::lock_guard<std::mutex> LockCriti(g_mutex_);
	if (wcslen(Sz_FileName_)!=0)
	{
		CTime Time_Current;
		Time_Current = CTime::GetCurrentTime();
		int nYear = Time_Current.GetYear();
		int nMonth = Time_Current.GetMonth();
		int nDay = Time_Current.GetDay();
		int nHour = Time_Current.GetHour();
		int nMinute = Time_Current.GetMinute();
		int nSecond = Time_Current.GetSecond();

		TCHAR Sz_TimeCopy[255] = { 0 };
		wsprintf(Sz_TimeCopy, L"%04d:%02d:%02d-%02d::%02d::%02d----", nYear, nMonth, nDay, nHour, nMinute, nSecond);
		LogWrite_.open(Sz_FileName_, std::ios::out | std::ios::ate | std::ios::app);
		if (LogWrite_.is_open())
		{
			LogWrite_ << Sz_Time;
			LogWrite_ << Sz_Content << "\t";
			LogWrite_ << Sz_Detail << "\n";

			LogWrite_.close();
		}
	}
}