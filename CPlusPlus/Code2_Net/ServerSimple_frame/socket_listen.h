#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>

#include "socket_work.h"

class Socket_Listen
{
public:
	Socket_Listen();
	~Socket_Listen();
public:
	void start(int port);
protected:
	void start_accept();
private:
	int socket_;
	struct sockaddr_in sockaddr_;
};