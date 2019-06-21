#pragma once

#include <string>

class ServerListen
{
public:
	ServerListen(){}

	virtual ~ServerListen(){}

	virtual void Start(int nport) {}

	virtual void DeleteSocket(int sockets) {}
};

class ServerAccepted
{
public:
	ServerAccepted(){}

	virtual ~ServerAccepted(){}

	virtual void RegisterSpi(ServerListen* spi) = 0;
};