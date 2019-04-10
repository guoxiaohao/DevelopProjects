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

struct Location
{
    double x;
    double y;
};

struct NodeInfo
{
    Location NodeLocate;
    double NodeWeight;   

    int nlens{0};
    int rValues[16];
    double dValues[16];
};

struct SupersInfo
{
    int strhour;
    int superarea;
    double areaweight;
    int demand;

    std::vector<Location> vecCenters;
    std::vector<NodeInfo> vecNodeInfos;
};