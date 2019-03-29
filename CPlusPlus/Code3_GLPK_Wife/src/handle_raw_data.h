#pragma once

#include <string>

class HandleRawData
{
public:
    HandleRawData();
    ~HandleRawData();
public:
    bool RecvData(const std::string& strData);
};