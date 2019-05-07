#include "pch.h"

#include "socket_work.h"

Socket_Work::Socket_Work()
{
}

Socket_Work::~Socket_Work()
{
}

int& Socket_Work::socket_assign()
{
	return socket_;
}

void Socket_Work::Start()
{
	std::cout << "Socket Starts Recv" << std::endl;
	
	while (true)
	{
		char szRecvBuff[512] = { 0 };
		int len = recv(socket_, szRecvBuff, sizeof(szRecvBuff) - 1, 0);

		if (len > 0)
		{
			std::cout << szRecvBuff << std::endl;
		}
		else
		{
			break;
		}
	}
	
	close(socket_);
	
	std::cout << "Socket Ends Recv" << std::endl;
}