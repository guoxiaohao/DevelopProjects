#include "pch.h"

#include "sqlite_writedata.h"

SqlWrite::SqlWrite()
{
}

SqlWrite::~SqlWrite()
{
}

SqlWrite1::SqlWrite1()
{
}

SqlWrite1::~SqlWrite1()
{
}

int SqlWrite1::GetTableRowNumber(std::string& strTableName)
{
    if(!global_sqlite1.IsDBConnectOK())
    {
        return -1;
    }

    int nRet = -1;
    const char *szErrMsg;
    char sql[1024] = {0};
    sprintf(sql, "select count(*) from %s", strTableName.c_str());

    sqlite3_stmt * stmt = NULL; 
    if( sqlite3_prepare_v2(global_sqlite1.m_lpDB, sql, -1, &stmt, &szErrMsg) == SQLITE_OK )
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

void SqlWrite1::DealDataSuperdaystable(PrepareParmStruct& paraStruct)
{
    if(!global_sqlite1.IsDBConnectOK())
    {
        return;
    }

    char szErrMsg[1024] = {0};
    char sql[1024] = {0};

    sprintf(sql, "insert into super_days_table (hour, super_area, area_weight, demand, centers, node_weight, locate_x, locate_y, r_values) values ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
    paraStruct.str_hour.c_str(), paraStruct.str_superIndex.c_str(), paraStruct.str_areaweightIndex.c_str(), paraStruct.str_demandIndex.c_str(), paraStruct.str_centersIndex.c_str(),
    paraStruct.str_nodeweightIndex.c_str(), paraStruct.str_latiIndex.c_str(), paraStruct.str_lontiIndex.c_str(), paraStruct.str_rvalueIndex.c_str());
    
    char* szErrs = szErrMsg;
    int rs = sqlite3_exec(global_sqlite1.m_lpDB, sql, 0, 0, &szErrs);
    if(rs!=SQLITE_OK)
    {
        std::cout << " Wrong -- Insert" << std::endl;
    }
    else
    {
        std::cout << " Right -- Insert" << std::endl;
    }
}

SqlWrite2::SqlWrite2()
{
}

SqlWrite2::~SqlWrite2()
{
}

int SqlWrite2::GetTableRowNumber(std::string& strTableName)
{
    if(!global_sqlite2.IsDBConnectOK())
    {
        return -1;
    }

    int nRet = -1;
    const char *szErrMsg;
    char sql[1024] = {0};
    sprintf(sql, "select count(*) from %s", strTableName.c_str());

    sqlite3_stmt * stmt = NULL; 
    if( sqlite3_prepare_v2(global_sqlite2.m_lpDB, sql, -1, &stmt, &szErrMsg) == SQLITE_OK )
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

void SqlWrite2::DealDataSuperdaystable(TeacherInfoStruct& paraStruct)
{
    if(!global_sqlite2.IsDBConnectOK())
    {
        return;
    }

    char szErrMsg[1024] = {0};
    char sql[1024] = {0};

    sprintf(sql, "insert into teacher_info_table (name, job, email) values ('%s', '%s', '%s')", paraStruct.str_name.c_str(), paraStruct.str_job.c_str(), paraStruct.str_email.c_str());
    
    char* szErrs = szErrMsg;
    int rs = sqlite3_exec(global_sqlite2.m_lpDB, sql, 0, 0, &szErrs);
    if(rs!=SQLITE_OK)
    {
        std::cout << " Wrong -- Insert" << std::endl;
    }
    else
    {
        std::cout << " Right -- Insert" << std::endl;
    }
}