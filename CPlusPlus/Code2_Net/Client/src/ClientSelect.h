#pragma once

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class ClientSelect
{
public:
    ClientSelect();
    ~ClientSelect();
public:
    void Connect(const uint32_t& nPort, const std::string& strIp);
private:
    bool bLoop;
};
