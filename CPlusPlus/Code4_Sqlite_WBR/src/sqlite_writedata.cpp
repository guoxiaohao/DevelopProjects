#include "pch.h"

#include "sqlite_writedata.h"

SqlWrite::SqlWrite()
{
}

SqlWrite::~SqlWrite()
{
}

bool SqlWrite::InitDBSqlite3(std::string& strDBName)
{
    int nRet = sqlite3_open(strDBName.c_str(), &m_lpDB);
    if(nRet!=SQLITE_OK)
    {
        m_bOpen = false;
        return false;
    }

    m_bOpen = true;
    return true;
}

void SqlWrite::UninitDBSqlite3()
{
    if(m_bOpen)
    {
        sqlite3_close(m_lpDB);
        m_bOpen = false;
    }
}

int SqlWrite::GetTableRowNumber(std::string& strTableName)
{
    if(!m_bOpen)
    {
        return -1;
    }

    int nRet = 0;
    const char *szErrMsg;
    char sql[1024] = "select count(*) from super_days_table";

    sqlite3_stmt * stmt = NULL; 
    if( sqlite3_prepare_v2(m_lpDB, sql, -1, &stmt, &szErrMsg) == SQLITE_OK )
    {
        while( sqlite3_step(stmt) == SQLITE_ROW )
        { 
            nRet = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
      std::cout << " Wrong -- select" << std::endl;
    }

    return nRet;
}

void SqlWrite::DealDataSuperdaystable(PrepareParmStruct& paraStruct)
{
    if(!m_bOpen)
    {
        return;
    }

    char szErrMsg[1024] = {0};
    char sql[1024] = {0};

    sprintf(sql, "insert into super_days_table (hour, super_area, area_weight, demand, centers, node_weight, locate_x, locate_y, r_values) values ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",
    paraStruct.str_hour.c_str(), paraStruct.str_superIndex.c_str(), paraStruct.str_areaweightIndex.c_str(), paraStruct.str_demandIndex.c_str(), paraStruct.str_centersIndex.c_str(),
    paraStruct.str_nodeweightIndex.c_str(), paraStruct.str_latiIndex.c_str(), paraStruct.str_lontiIndex.c_str(), paraStruct.str_rvalueIndex.c_str());
    
    char* szErrs = szErrMsg;
    int rs = sqlite3_exec(m_lpDB, sql, 0, 0, &szErrs);
    if(rs!=SQLITE_OK)
    {
        std::cout << " Wrong -- Insert" << std::endl;
    }
    else
    {
        std::cout << " Right -- Insert" << std::endl;
    }
} 