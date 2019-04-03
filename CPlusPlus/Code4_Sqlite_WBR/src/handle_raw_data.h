#pragma once

#include <functional>
#include <string>
#include "predefine.h"

class HandleRawData
{
public:
    HandleRawData();
    ~HandleRawData();
public:
    bool RecvData(const std::string& strData, std::function< void(PrepareParmStruct&) > funcs);
};