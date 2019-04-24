#include "pch.h"

#include "handle_database.h"
#include "generate_data.h"

int main(int argc, char** argv)
{   
    std::string DBName = "/home/guoxy/DBSqlite/supers_days.db";
    bool brets = global_sqlite.InitSqlite(DBName);
    if(!brets)
    {
        std::cout << "Wrong -- DataBase Startup" << std::endl;
        return 1;
    }

    HandleDB handledbs;
    GenerateData generateDatas;

    handledbs.HandleDataFromDB();
    generateDatas.ResetInfos();
    handledbs.TravelData(std::bind(&GenerateData::TravelGenerate, &generateDatas, std::placeholders::_1, std::placeholders::_2));
    generateDatas.MySolutions();

    global_sqlite.UninitSqlite();
    return 0;
};