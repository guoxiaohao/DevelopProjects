#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>

class Socket_Work
{
public:
	Socket_Work();
	~Socket_Work();
public:
	int& socket_assign();
	void Start();
private:
	int socket_;
};