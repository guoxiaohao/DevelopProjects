#include "sqlite_operator.h"



SqliteOpe::SqliteOpe()
{
    m_bOk = false;
}

SqliteOpe::~SqliteOpe()
{
}

bool SqliteOpe::InitSqlite(std::string& strDBName)
{
    int nRet = sqlite3_open(strDBName.c_str(), &m_lpDB);
    if(nRet != SQLITE_OK)
    {
        m_bOk = false;
        return m_bOk;
    }

    m_bOk = true;
    return m_bOk;
}

void SqliteOpe::UninitSqlite()
{
    if(m_bOk)
    {
        sqlite3_close(m_lpDB);
        m_bOk = false;
    }
}

bool SqliteOpe::IsDBConnectOK()
{
    return m_bOk;
}
