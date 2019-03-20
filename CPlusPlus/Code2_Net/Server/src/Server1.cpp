#include "pch.h"

#include "Server1.h"

CServer1::CServer1()
{
	bLoop = true;
}

CServer1::~CServer1()
{
}

void CServer1::StartUp(uint32_t nPort)
{
	sockaddr_in addrListen;
	memset(&addrListen, 0, sizeof(addrListen));
	addrListen.sin_family = AF_INET;
	addrListen.sin_port = htons(nPort);
	addrListen.sin_addr.s_addr = htonl(INADDR_ANY);
    
	int socketListen = socket(AF_INET, SOCK_STREAM, 0);
	if (socketListen<0)
	{
		std::cout << "Wrong - Server Init Socket" << std::endl;
		return;
	}

	bind(socketListen, (sockaddr*)&addrListen, sizeof(addrListen));
	listen(socketListen, 5);

    
	sockaddr_in addrAccept;
	memset(&addrAccept, 0, sizeof(addrAccept));
	socklen_t nLens = sizeof(addrAccept);

	std::shared_ptr<int> lpSocketAccept = std::make_shared<int>();
	std::cout << "Wait for ..." << std::endl;
	*lpSocketAccept = accept(socketListen, (sockaddr*)&addrAccept, &nLens);

	std::thread threadSer([&lpSocketAccept]()
	{
		std::cout << "Right Server Recv Data" << std::endl;
		while (true)
		{
			char szRecvBuff[512] = { 0 };
			int len = recv(*lpSocketAccept, szRecvBuff, sizeof(szRecvBuff) - 1, 0);
			if (len > 0)
			{
				std::cout << szRecvBuff << std::endl;
			}
			else
			{
				break;
			}
		}
	});

	threadSer.join();
	std::cout << "End" << std::endl;

	close(*lpSocketAccept);
	close(socketListen);
}
