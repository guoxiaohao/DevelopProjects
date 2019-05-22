#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include "sdk_network.h"

class ConnectorImpl:public Connector 
{
public:
	virtual ~ConnectorImpl(){}

	virtual void Release();

	virtual void RegisterSpi(ConnectorSpi* spi);

	virtual void Connect(std::string& ip, int port);

	virtual void SendMessage(const std::string& msg);

	virtual void RecvMessage();
protected:
	ConnectorSpi* spi_;
	int socket_;
};

Connector* CreateConnectorObj();

class ClientSpi:public ConnectorSpi
{
public:
	ClientSpi();
	virtual ~ClientSpi();

	virtual void OnConnected(int result);

	virtual void OnDisconnected();

	virtual void OnMessage(std::string msg);
public:
	void Start();
protected:
	Connector* connector_ {nullptr};

	std::string str_ip_;
	int nport_;
};