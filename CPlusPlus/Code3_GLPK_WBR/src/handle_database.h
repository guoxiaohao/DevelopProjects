#pragma once

#include "predefine.h"

class HandleDB
{
public:
    HandleDB();
    ~HandleDB();
public:
    void HandleDataFromDB();
    void TravelData();
protected:
    TargetInfosArr m_datas;
};
