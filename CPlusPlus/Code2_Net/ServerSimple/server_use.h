#pragma once

#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>

class ServerUse
{
public:
	ServerUse(){}
	~ServerUse(){}

	int& socket();
	void Start();
protected:
	void RecvData();

	int socket_;
};