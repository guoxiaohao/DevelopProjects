#include "pch.h"

#include "string.h"
#include "handle_database.h"

HandleDB::HandleDB()
{
}

HandleDB::~HandleDB()
{
}

void HandleDB::HandleDataFromDB()
{
    if(!global_sqlite.IsDBConnectOK())
    {
        return;
    }

    const char *szErrMsg;
    char sql[1024] = "select distinct hour from super_days_table";

    sqlite3_stmt * stmt = NULL; 
    if( sqlite3_prepare_v2(global_sqlite.m_lpDB, sql, -1, &stmt, &szErrMsg) == SQLITE_OK )
    {
        m_datas.nlen = 0;
        while( sqlite3_step(stmt) == SQLITE_ROW )
        {
            std::string hour = (char*)sqlite3_column_text(stmt, 0);
            m_datas.ArrInfos[m_datas.nlen].strhour = hour;
            m_datas.nlen++;
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cout << " Wrong -- select" << std::endl;
        return;
    }

    for(int i=0; i<m_datas.nlen; i++)
    {
        std::string strVal = m_datas.ArrInfos[i].strhour;
        memset(sql, 0, sizeof(sql));
        sprintf(sql, "select distinct super_area from super_days_table where hour='%s'", strVal.c_str());
        
        if( sqlite3_prepare_v2(global_sqlite.m_lpDB, sql, -1, &stmt, &szErrMsg) == SQLITE_OK )
        {
            m_datas.ArrInfos[i].vecAreas.clear();
            while( sqlite3_step(stmt) == SQLITE_ROW )
            {
                std::string super_area = (char*)sqlite3_column_text(stmt, 0);
                m_datas.ArrInfos[i].vecAreas.push_back(super_area);
            }
            sqlite3_finalize(stmt);
        }
    }
}

void HandleDB::TravelData(std::function<void(std::string&, std::string&)> funcs)
{
    if(m_datas.nlen>0)
    {
        for(int i=0; i<m_datas.nlen; i++)
        {
            std::string hours = m_datas.ArrInfos[i].strhour;
            for(int j=0; j<m_datas.ArrInfos[i].vecAreas.size(); j++)
            {
                std::string super_areas = m_datas.ArrInfos[i].vecAreas[j];

                funcs(hours, super_areas);
            }
        }
    }
}