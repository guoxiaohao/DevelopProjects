#pragma once

#include <string>
#include "sqlite3.h"
#include "predefine.h"

class SqlWrite
{
public:
    SqlWrite();
    ~SqlWrite();
public:
    bool InitDBSqlite3(std::string& strDBName);
    void UninitDBSqlite3();
    int GetTableRowNumber(std::string& strTableName);
    void DealDataSuperdaystable(PrepareParmStruct& paraStruct);
protected:
    bool m_bOpen;
    sqlite3 *m_lpDB;
};