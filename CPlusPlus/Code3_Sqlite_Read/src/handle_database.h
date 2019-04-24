#pragma once

#include <functional>
#include "predefine.h"

class HandleDB
{
public:
    HandleDB();
    ~HandleDB();
public:
    void HandleDataFromDB();
    void TravelData(std::function<void(std::string&, std::string&)> funcs);
protected:
    TargetInfosArr m_datas;
};
