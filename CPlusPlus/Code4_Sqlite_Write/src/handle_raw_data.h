#pragma once

#include <functional>
#include <string>
#include "predefine.h"

class HandleRawData1
{
public:
    HandleRawData1();
    ~HandleRawData1();
public:
    bool RecvData(const std::string& strData, std::function< void(PrepareParmStruct&) > funcs);
};

class HandleRawData2
{
public:
    HandleRawData2();
    ~HandleRawData2();
public:
    bool RecvData(const std::string& strData, std::function< void(TeacherInfoStruct&) > funcs);
protected:
    int partTotal;
    TeacherInfoStruct m_structVal;
};