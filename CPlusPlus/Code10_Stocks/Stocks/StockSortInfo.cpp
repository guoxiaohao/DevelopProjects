#include "StockSortInfo.h"

#include <fstream>

namespace guoxh{

bool StockSort::Init(std::string file_path)
{
    if (access(file_path.c_str(), 0) != 0)
    {
        return false;
    }

    std::fstream Fstream; 
    Fstream.open(file_path.c_str(), std::ios::in);
    if(!Fstream.is_open())
    {
        return false;
    }

    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(Fstream, root))
    {
        Fstream.close();
        return false;
    }

    for(size_t i = 0; i < root["industry_def"].size(); i++)
    {
        StockInfo tmp;
        tmp.industry_id = root["industry_def"][i]["id"].asInt();
        tmp.industry_name = root["industry_def"][i]["name"].asString();
        map_stock_info.insert(std::make_pair(tmp.industry_id, tmp));
    }
    for(size_t i = 0; i < root["stocks_def"].size(); i++)
    {
        StocksDef tmp;
        tmp.code = root["stocks_def"][i]["code"].asString();
        tmp.name = root["stocks_def"][i]["name"].asString();
        int ids = root["stocks_def"][i]["industry"].asInt();

        auto iters = map_stock_info.find(ids);
        if(iters!=map_stock_info.end())
        {
            iters->second.stocks.push_back(tmp);
        }
    }

    return true;
}

void StockSort::UnInit()
{
}

void StockSort::DisplayData()
{
    for(auto &elems:map_stock_info)
    {
        std::cout << "industry_id: " << elems.second.industry_id << " , "  << "industry_name: " << elems.second.industry_name << std::endl;
        for (size_t i = 0; i < elems.second.stocks.size(); i++)
        {
            std::cout<< ">>>>" << "code: " << elems.second.stocks[i].code << " , " << "name: " << elems.second.stocks[i].name << std::endl;
        }
    }
}

}