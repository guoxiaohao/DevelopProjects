#include "pch.h"

#include <algorithm>
#include "handle_raw_data.h"

HandleRawData1::HandleRawData1()
{

}

HandleRawData1::~HandleRawData1()
{

}

bool HandleRawData1::RecvData(const std::string& strData, std::function< void(PrepareParmStruct&) > funcs)
{
    std::string strValues = strData;
    PrepareParmStruct tmpData;

    int nPos = strValues.find_first_of(',');
    std::string str_hour = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_hour = str_hour;

    nPos = strValues.find_first_of(',');
    std::string str_superIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_superIndex = str_superIndex;

    nPos = strValues.find_first_of(',');
    std::string str_areaweightIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_areaweightIndex = str_areaweightIndex;

    nPos = strValues.find_first_of(',');
    std::string str_demandIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_demandIndex = str_demandIndex;

    nPos = strValues.find_first_of('"');
    strValues = strValues.substr(nPos+1, strValues.length());
    nPos = strValues.find_first_of('"');
    std::string str_centersIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    nPos = strValues.find_first_of(',');
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_centersIndex = str_centersIndex;

    nPos = strValues.find_first_of(',');
    std::string str_nodeweightIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_nodeweightIndex = str_nodeweightIndex;

    nPos = strValues.find_first_of(',');
    std::string str_latiIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_latiIndex = str_latiIndex;

    nPos = strValues.find_first_of(',');
    std::string str_lontiIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_lontiIndex = str_lontiIndex;

    nPos = strValues.find_first_of('"');
    strValues = strValues.substr(nPos+1, strValues.length());
    nPos = strValues.find_first_of('"');
    std::string str_rvalueIndex = strValues.substr(0, nPos);
    strValues = strValues.substr(nPos+1, strValues.length());
    tmpData.str_rvalueIndex = str_rvalueIndex;

    if(funcs!=nullptr)
    {
        funcs(tmpData);
    }

    return true;
}

HandleRawData2::HandleRawData2()
{
    partTotal = 0;
}

HandleRawData2::~HandleRawData2()
{
}

bool HandleRawData2::RecvData(const std::string& strData, std::function< void(TeacherInfoStruct&) > funcs)
{
    std::string strValues = strData;
    strValues.erase(std::remove(strValues.begin(), strValues.end(), ' '), strValues.end());
    strValues.erase(std::remove(strValues.begin(), strValues.end(), '\r'), strValues.end());
    
    if(strData=="")
    {
        return false;
    }

    partTotal++;
    switch(partTotal)
    {
        case 1:
            break;
        case 2:
            {
                m_structVal.str_name = strData;
            }
            break;
        case 3:
            {
                m_structVal.str_job = strData;
            }
            break;
        case 4:
            {
                m_structVal.str_email = strData;
                if(funcs!=nullptr)
                {
                    funcs(m_structVal);
                }
                partTotal = 0;
            }
            break;
        default:
            break;
    }

    return true;
}