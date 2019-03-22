#pragma once

#include "boost/asio.hpp"

class ClientSyncBoost
{
public:
	ClientSyncBoost();
	~ClientSyncBoost();
public:
	void Connect(const uint32_t& nPort, const std::string& strIp);
private:
	boost::asio::io_service g_io_service;
};
