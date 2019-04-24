#pragma once

#include <string>
#include "sqlite3.h"
#include "predefine.h"

class SqlWrite
{
public:
    SqlWrite();
    virtual ~SqlWrite();
public:
    virtual int GetTableRowNumber(std::string& strTableName) = 0;
};

class SqlWrite1:public SqlWrite
{
public:
    SqlWrite1();
    virtual ~SqlWrite1();
public:
    virtual int GetTableRowNumber(std::string& strTableName) override;
    void DealDataSuperdaystable(PrepareParmStruct& paraStruct);
};

class SqlWrite2:public SqlWrite
{
public:
    SqlWrite2();
    virtual ~SqlWrite2();
public:
    virtual int GetTableRowNumber(std::string& strTableName) override;
    void DealDataSuperdaystable(TeacherInfoStruct& paraStruct);
};