#include "pch.h"

#include "handle_database.h"

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
    handledbs.HandleDataFromDB();
    handledbs.TravelData();

    global_sqlite.UninitSqlite();
    return 0;
};