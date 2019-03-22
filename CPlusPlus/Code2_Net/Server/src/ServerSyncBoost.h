#pragma once

#include "boost/asio.hpp"

class ServerSyncBoost
{
public:
    ServerSyncBoost();
    ~ServerSyncBoost();
public:
    void StartUp(const uint32_t& nPort);
private:
	boost::asio::io_service g_io_service;
};