#pragma once

#include "boost/asio.hpp"

class ClientASyncBoost
{
public:
	ClientASyncBoost();
	~ClientASyncBoost();
public:
	void Connect(const uint32_t& nPort, const std::string& strIp);
private:
	void Handle_Connect(const boost::system::error_code&);
	void Handle_Write(const boost::system::error_code&);
private:
	boost::asio::io_service g_io_service;
};
