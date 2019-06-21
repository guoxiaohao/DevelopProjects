#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "client_base.h"

class ConnectorImpl:public Connector 
{
public:
	virtual ~ConnectorImpl(){}

	virtual void Release();

	virtual void RegisterSpi(ConnectorSpi* spi);

	virtual void Connect(std::string& ip, int port);

	virtual void SendMessage(std::string msg);

	virtual void EnableWorkThread();

	virtual void DoWorkThread();
protected:
	void do_connect(std::string& ip, int port);
	void do_send(std::string msg);

	bool bLoop{false};

	ConnectorSpi* spi_{nullptr};
	int socket_;
	boost::asio::io_service io_service_;
	std::shared_ptr<boost::asio::deadline_timer> deadline_timers;
};

Connector* CreateConnectorObj();

class ClientSpi:public ConnectorSpi
{
public:
	ClientSpi();
	virtual ~ClientSpi();

	void Start();
public:
	virtual void OnConnected(int result);

	virtual void OnDisconnected();

	virtual void OnMessage(std::string msg);
protected:
	Connector* connector_ {nullptr};

	std::string str_ip_;
	int nport_;
};