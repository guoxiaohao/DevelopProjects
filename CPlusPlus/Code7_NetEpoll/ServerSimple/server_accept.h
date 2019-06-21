#pragma once

#include <memory>
#include <map>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server_base.h"
#include "server_use.h"

class ServerSocket:public ServerListen
{
public:
	ServerSocket(){}
	~ServerSocket(){}

	virtual void Start(int nport) override;
	virtual void DeleteSocket(int sockets) override;
protected:
	void start_accept();

	int socket_;
	std::map<int, std::shared_ptr<ServerUse> > map_accept_sockets;
};