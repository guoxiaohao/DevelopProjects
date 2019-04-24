#pragma once

#include <vector>
#include <string>
#include "predefine.h"

class GenerateData
{
public:
    GenerateData();
    ~GenerateData();

    void ResetInfos();
    void TravelGenerate(std::string& tHour, std::string& tArea);
    void MySolutions();
private:
    std::vector<SupersInfo> vecInfos;
    int m_nTotal{0};
};