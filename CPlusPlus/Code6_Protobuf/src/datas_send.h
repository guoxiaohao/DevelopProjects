#pragma once

#include <functional>
#include <string>
#include "sdk_files_write.h"

class DataSend
{
public:
	DataSend();
	~DataSend();
public:
	void DataSendFunction1(std::string& strcontent, std::function<void(std::string&)> func);
	void DataSendFunction2(std::string& strcontent, std::function<void(std::string&)> func);
protected:
#ifdef MACRO_SAVE_FILE
	SDK_FILES::FilesWrite m_files;
#endif
};