#pragma once

#include <string>
#include <vector>

struct TargetInfos
{
    std::string strhour;
    std::vector<std::string> vecAreas;
};

struct TargetInfosArr
{
    int nlen{0};

    TargetInfos ArrInfos[25];
};