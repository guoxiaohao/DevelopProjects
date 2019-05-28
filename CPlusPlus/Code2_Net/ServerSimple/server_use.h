#pragma once

#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server_base.h"

class ServerUse:public ServerAccepted
{
public:
	ServerUse(){}
	~ServerUse()
	{
		lpthread->join();
		std::cout << "socket " << socket_ << " deconstruct" << std::endl;
	}

	virtual void RegisterSpi(ServerListen* spi) override;

	int& socket();
	void Start();
protected:
	void RecvData();

	ServerListen* _spi;
	int socket_;
	std::shared_ptr< std::thread > lpthread;
};