#include "pch.h"

#include "result_json.h"

ResultJson::ResultJson()
{
}

ResultJson::~ResultJson()
{
}

bool ResultJson::Init()
{
	m_fstream.open("reslut_datas.json", std::ios::out | std::ios::trunc);
	if(m_fstream.is_open())
	{
		m_fstream.close();
		m_fstream.open("reslut_datas.json", std::ios::out | std::ios::ate | std::ios::app);
		if(!m_fstream.is_open())
		{
			return false;
		}
		
		return true;
	}
	else
	{
		return false;
	}
}
	
void ResultJson::Uninit()
{
	if(m_fstream.is_open())
	{
		m_fstream.close();
	}
}

void ResultJson::WriteDatas(double* arryDouble, int nNums)
{
	if(m_fstream.is_open())
	{
		m_jsonValue.clear();
		m_jsonValue["TargetValue"] = (double)arryDouble[0];
		m_fstream << m_jsonWriter.write(m_jsonValue);
		m_fstream.flush();
		
		m_fstream << '\t' << '\t';
		m_jsonValue.clear();
		for(int i=0;i<nNums-1;i++)
		{
			char szName[16] = {0};
			sprintf(szName, "Para%d", i+1);
			m_jsonValue[szName] = arryDouble[1+i];
		}
		m_fstream << m_jsonWriter.write(m_jsonValue);
		m_fstream.flush();
	}	
}