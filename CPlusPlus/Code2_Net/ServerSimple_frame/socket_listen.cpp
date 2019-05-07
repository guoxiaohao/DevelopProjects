#include "pch.h"

#include <memory>
#include "socket_listen.h"

Socket_Listen::Socket_Listen()
{
}

Socket_Listen::~Socket_Listen()
{
}

void Socket_Listen::start(int port)
{
	memset(&sockaddr_, 0, sizeof(sockaddr_));
	sockaddr_.sin_family = AF_INET;
	sockaddr_.sin_port = htons(port);
	sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);

	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_<0)
	{
		std::cout << "Wrong - Listen Socket Init" << std::endl;
		return;
	}

	bind(socket_, (sockaddr*)&sockaddr_, sizeof(sockaddr_));
	listen(socket_, 5);

	start_accept();
}

void Socket_Listen::start_accept()
{
	std::shared_ptr<Socket_Work> lpsocket = std::make_shared<Socket_Work>();
	
	sockaddr_in addrAccept;
	memset(&addrAccept, 0, sizeof(addrAccept));
	socklen_t nLens = sizeof(addrAccept);
	lpsocket->socket_assign() = accept(socket_, (sockaddr*)&addrAccept, &nLens);
	
	lpsocket->Start();
}