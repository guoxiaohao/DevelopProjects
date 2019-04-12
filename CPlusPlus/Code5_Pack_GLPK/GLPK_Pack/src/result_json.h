#pragma once

#include <fstream>
#include "json/json.h"

class ResultJson
{
public:
	ResultJson();
	~ResultJson();
public:
	bool Init();
	void Uninit();
	void WriteDatas(double* arryDouble, int nNums);
protected:
	std::fstream m_fstream;
	Json::FastWriter m_jsonWriter;
	Json::Value m_jsonValue;
};