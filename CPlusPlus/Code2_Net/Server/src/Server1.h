#pragma once

#include "sys/socket.h"
#include "arpa/inet.h"

class CServer1
{
public:
    CServer1();
    ~CServer1();
public:
    void StartUp(uint32_t nPort);
private:
    bool bLoop;
};
