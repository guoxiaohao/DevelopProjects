#include "pch.h"

#include "datas_send.h"

DataSend::DataSend()
{
#ifdef MACRO_SAVE_FILE
	std::string tFileName = "protoContent.txt";
	m_files.SetFileName(tFileName);
	m_files.TruncFile();
#endif
}

DataSend::~DataSend()
{
}

void DataSend::DataSendFunction1(std::string& strcontent, std::function<void(std::string&)> func)
{
	if(func)
	{
		func(strcontent);
	}
#ifdef MACRO_SAVE_FILE
	m_files.WriteLine(strcontent);
#endif
}

void DataSend::DataSendFunction2(std::string& strcontent, std::function<void(std::string&)> func)
{
	if(func)
	{
		func(strcontent);
	}
#ifdef MACRO_SAVE_FILE
	m_files.WriteLine(strcontent);
#endif
}