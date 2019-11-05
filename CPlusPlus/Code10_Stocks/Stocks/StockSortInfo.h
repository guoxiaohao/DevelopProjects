#pragma once

#include <unistd.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <json/json.h>

namespace guoxh{

struct StocksDef
{
    std::string code;
    std::string name;
};

struct StockInfo
{
    int industry_id;
    std::string industry_name;
    std::vector<StocksDef> stocks;
};

class StockSort
{
public:
    bool Init(std::string file_path);
    void UnInit();
    
    void DisplayData();
protected:
    std::unordered_map<int, StockInfo> map_stock_info;
};

}