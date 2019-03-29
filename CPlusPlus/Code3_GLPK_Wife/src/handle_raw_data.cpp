#include "pch.h"

#include "handle_raw_data.h"

HandleRawData::HandleRawData()
{

}

HandleRawData::~HandleRawData()
{

}

bool HandleRawData::RecvData(const std::string& strData)
{
    std::string strValues = strData;
    int nPos = strValues.find_first_of(',');
    std::string str_hour = strValues.substr(0, nPos);
    strValues = strValues.substr()
	std::string str_superIndex= this.findColumnIndex(worksheet.getRow(0), "Super Area");
	std::string str_areaweightIndex=this.findColumnIndex(worksheet.getRow(0), "Area Weight");		
	std::string str_demandIndex= this.findColumnIndex(worksheet.getRow(0), "Demand");
	std::string str_centersIndex=this.findColumnIndex(worksheet.getRow(0), "Centers");		
	std::string str_nodeweightIndex= this.findColumnIndex(worksheet.getRow(0), "Node Weight"); 
	std::string str_latiIndex=this.findColumnIndex(worksheet.getRow(0), "Location.x");		
	std::string str_lontiIndex= this.findColumnIndex(worksheet.getRow(0), "Location.y");
	std::string str_rvalueIndex= this.findColumnIndex(worksheet.getRow(0), "R values");

    return true;
}