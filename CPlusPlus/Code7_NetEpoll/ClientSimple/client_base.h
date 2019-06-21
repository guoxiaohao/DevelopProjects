#pragma once

#include <string>

class ConnectorSpi
{
public:
	virtual ~ConnectorSpi(){}

	virtual void OnConnected(int result){}

	virtual void OnDisconnected(){}

	virtual void OnMessage(std::string msg) {}

	virtual void SendMessage(const std::string& msg) {}
};

class Connector
{
public:
	virtual ~Connector(){}

	virtual void Release() = 0;

	virtual void RegisterSpi(ConnectorSpi* spi) = 0;

	virtual void Connect(std::string& ip, int port) = 0;

	virtual void SendMessage(std::string msg) = 0;

	virtual void EnableWorkThread() = 0;

	virtual void DoWorkThread() = 0;
};