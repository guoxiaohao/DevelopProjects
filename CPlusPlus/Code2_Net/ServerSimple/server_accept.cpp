#include "pch.h"

#include <string.h>
#include "server_accept.h"

void ServerSocket::Start(int nport)
{
	struct sockaddr_in addrListen;
	memset(&addrListen, 0, sizeof(addrListen));
	addrListen.sin_family = AF_INET;
	addrListen.sin_port = htons(nport);
	addrListen.sin_addr.s_addr = htonl(INADDR_ANY);

	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_<0)
	{
		std::cout << "Wrong - Listen Socket Init" << std::endl;
		return;
	}

	bind(socket_, (sockaddr*)&addrListen, sizeof(addrListen));
	listen(socket_, 5);
	start_accept();
}

void ServerSocket::start_accept()
{
	std::cout << "Start Accept" << std::endl;
	while(true)
	{
		std::shared_ptr<ServerUse> tmp_ptr = std::make_shared<ServerUse>();

		sockaddr_in addrAccept;
		memset(&addrAccept, 0, sizeof(addrAccept));
		socklen_t nLens = sizeof(addrAccept);

		tmp_ptr->socket() = accept(socket_, (sockaddr*)&addrAccept, &nLens);
		tmp_ptr->RegisterSpi(this);
		tmp_ptr->Start();
		map_accept_sockets.insert(std::make_pair(tmp_ptr->socket(), tmp_ptr));
	}
}

void ServerSocket::DeleteSocket(int sockets)
{
	std::map<int, std::shared_ptr<ServerUse> >::iterator iter;
	iter = map_accept_sockets.find(sockets);
	if(iter!=map_accept_sockets.end())
	{
		std::cout << "sockets " << sockets << " should be deleted" << std::endl;
	}
}