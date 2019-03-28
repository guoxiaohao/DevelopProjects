#pragma once

#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class ServerSelect
{
public:
    ServerSelect();
    ~ServerSelect();
public:
    void StartUp(const uint32_t& nPort);
private:
    bool bLoop;
};
