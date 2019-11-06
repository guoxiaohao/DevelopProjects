#include "pch.h"

#include "MyRedis.h"

namespace guoxh{

void Redis::SetValue(std::string ip, int port)
{
    ip_ = ip;
    port_ = port;
}

bool Redis::Connect()
{
    rediscontext_ = redisConnect(ip_.c_str(), port_);
    if(!rediscontext_)
    {
        return false;
    }

    if(rediscontext_->err)
    {
        redisFree(rediscontext_);
        return false;
    }

    return true;
}

void Redis::DisConnect()
{
    if(rediscontext_)
    {
        redisFree(rediscontext_);
    }
}

void Redis::EnsureKeyNotExist(const char* sz_key)
{
    redisreply_ = (redisReply*)redisCommand(rediscontext_, "exists %s", sz_key);
    int nret = 0;
    if(redisreply_->type == REDIS_REPLY_INTEGER)
    {
        if(redisreply_->integer == 1L)
        {
            nret = 1;
        }
    }
    if(nret==0)
    {
        std::cout << "key: " << sz_key << ", not exist"<< std::endl;
        freeReplyObject(redisreply_);
        return;
    }

    if(DeleteKey(sz_key))
    {
        std::cout << "key: " << sz_key << ", delete success"<< std::endl;
    }
    else
    {
        std::cout << "key: " << sz_key << ", delete failed"<< std::endl;
    }
}

bool Redis::DeleteKey(const char* sz_key)
{
    bool bret = false;
    redisreply_ = (redisReply*)redisCommand(rediscontext_, "DEL %s", sz_key);
    if(redisreply_->type == REDIS_REPLY_INTEGER)
    {
        if(redisreply_->integer == 1L)
        {
            bret = false;
        }
        else
        {
            bret = true;
        }
    }

    freeReplyObject(redisreply_);
    return bret;
}

bool Redis::SetPair(const char* sz_key, const char* sz_value)
{
    redisreply_ = (redisReply*)redisCommand(rediscontext_, "SET %s %s", sz_key, sz_value);
    if(!redisreply_)
    {
        return false;
    }
    freeReplyObject(redisreply_);
    return true;
}

std::string Redis::GetValue(const char* sz_key)
{
    std::string str_ret ="";
    redisreply_ = (redisReply*)redisCommand(rediscontext_, "GET %s", sz_key);
    if(!redisreply_)
    {
        return str_ret;
    }

    str_ret = redisreply_->str;
    freeReplyObject(redisreply_);
    return str_ret;
}

}