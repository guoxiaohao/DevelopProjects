#pragma once

#include "sys/socket.h"
#include "arpa/inet.h"

class ClientSync
{
public:
    ClientSync();
    ~ClientSync();
public:
    void Connect(const uint32_t& nPort, const std::string& strIp);
};
