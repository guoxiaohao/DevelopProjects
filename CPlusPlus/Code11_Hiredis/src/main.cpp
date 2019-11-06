#include "pch.h"

#include "MyRedis.h"

int main(int argc, char** argv)
{
    guoxh::Redis my_redis;
    my_redis.SetValue("127.0.0.1", 6379);
    std::string str_key = "guoxh";

    if(!my_redis.Connect())
    {
        std::cout << "Redis Connect Error" << std::endl;
        return 1;
    }
    
    my_redis.EnsureKeyNotExist(str_key.c_str());
    if (my_redis.SetPair(str_key.c_str(), "sb"))
    {
        std::string str_val = my_redis.GetValue(str_key.c_str());
        std::cout << "key: " << str_key << " , " << "value: " << str_val << std::endl;
    }
    
    my_redis.DisConnect();
    return 0;
}