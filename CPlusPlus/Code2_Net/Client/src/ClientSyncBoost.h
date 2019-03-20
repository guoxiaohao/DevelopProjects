#pragma once

#include "boost/asio.hpp"

class ClientSyncBoost
{
public:
	ClientSyncBoost();
	~ClientSyncBoost();
public:
	void Startup(int nPort, char* szIp);
private:
	boost::asio::io_service g_io_service;
};
