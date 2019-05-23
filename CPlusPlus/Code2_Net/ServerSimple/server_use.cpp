#include "pch.h"

#include <signal.h>
#include "server_use.h"

int& ServerUse::socket()
{
	return socket_;
}

void ServerUse::Start()
{
	std::thread threads(&ServerUse::RecvData, this);
	threads.detach();
}

void ServerUse::RecvData()
{
	std::cout << "Begin Recv Data" << std::endl;
	while (true)
	{
		char szRecvBuff[512] = { 0 };
		int len = recv(socket_, szRecvBuff, sizeof(szRecvBuff), 0);

		if (len > 0)
		{
			std::cout << szRecvBuff << std::endl;
		}
		else
		{
			break;
		}
	}

	std::cout << "Connect Closed" << std::endl;
}