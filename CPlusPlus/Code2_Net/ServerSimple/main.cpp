#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TARGET_VALUE_PORT			10006

int main(int argc, char** argv)
{
	struct sockaddr_in addrListen;
	memset(&addrListen, 0, sizeof(addrListen));
	addrListen.sin_family = AF_INET;
	addrListen.sin_port = htons(TARGET_VALUE_PORT);
	addrListen.sin_addr.s_addr = htonl(INADDR_ANY);

	int socketListen = socket(AF_INET, SOCK_STREAM, 0);
	if (socketListen<0)
	{
		std::cout << "Wrong - Listen Socket Init" << std::endl;
		return 1;
	}

	bind(socketListen, (sockaddr*)&addrListen, sizeof(addrListen));
	listen(socketListen, 5);

	sockaddr_in addrAccept;
	memset(&addrAccept, 0, sizeof(addrAccept));
	socklen_t nLens = sizeof(addrAccept);
	int socketAccept = accept(socketListen, (sockaddr*)&addrAccept, &nLens);

	std::cout << "Right Accept Socket" << std::endl;
	while (true)
	{
		char szRecvBuff[512] = { 0 };
		int len = recv(socketAccept, szRecvBuff, sizeof(szRecvBuff) - 1, 0);

		if (len > 0)
		{
			std::cout << szRecvBuff << std::endl;
		}
		else
		{
			break;
		}
	}
	
	close(socketAccept);
	close(socketListen);
	std::cout << "Ends" << std::endl;

	return 0;
}