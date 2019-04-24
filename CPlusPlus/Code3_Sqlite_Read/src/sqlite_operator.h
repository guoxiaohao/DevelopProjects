#pragma once

#include <string>
#include "sqlite3.h"

class SqliteOpe
{
public:
    SqliteOpe();
    ~SqliteOpe();
public:
    bool InitSqlite(std::string& strDBName);
    void UninitSqlite();
    bool IsDBConnectOK();
public:
    sqlite3 *m_lpDB;
protected:
    bool m_bOk;
};