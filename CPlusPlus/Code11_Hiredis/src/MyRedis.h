#pragma once

#include <hiredis/hiredis.h>

namespace guoxh{

class Redis
{
public:
    void SetValue(std::string ip, int port);
    bool Connect();
    void DisConnect();

    void EnsureKeyNotExist(const char* sz_key);
    bool DeleteKey(const char* sz_key);

    bool SetPair(const char* sz_key, const char* sz_value);
    std::string GetValue(const char* sz_key);
protected:
    std::string ip_;
    int port_;

    redisContext * rediscontext_{nullptr};
    redisReply * redisreply_{nullptr};
};

}