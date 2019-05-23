#pragma once

#include <memory>
#include <map>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server_use.h"

class ServerAccept
{
public:
	ServerAccept(){}
	~ServerAccept(){}

	void Start();
protected:
	void start_accept();

	int socket_;
	std::map<int, std::shared_ptr<ServerUse> > map_accept_sockets;
};