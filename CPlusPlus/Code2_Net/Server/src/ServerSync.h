#pragma once

#include "sys/socket.h"
#include "arpa/inet.h"

class ServerSync
{
public:
    ServerSync();
    ~ServerSync();
public:
    void StartUp(const uint32_t& nPort);
};
