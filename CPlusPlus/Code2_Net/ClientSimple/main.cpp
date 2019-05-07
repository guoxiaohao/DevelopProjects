#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TARGET_VALUE_IP				"127.0.0.1"
#define TARGET_VALUE_PORT			10006

int main(int argc, char** argv)
{
	struct sockaddr_in addrSend;
	memset(&addrSend, 0, sizeof(addrSend));
	addrSend.sin_family = AF_INET;
	addrSend.sin_port = htons(TARGET_VALUE_PORT);
	addrSend.sin_addr.s_addr = inet_addr(TARGET_VALUE_IP);

	int socketSend = socket(AF_INET, SOCK_STREAM, 0);
	if(socketSend<0)
	{
		std::cout << "Wrong - Init Socket" << std::endl;
		return 1;
	}

	while(connect(socketSend, (struct sockaddr*)&addrSend, sizeof(addrSend))!=0);
	std::cout << "Right - Connect " << std::endl;

	int i = 0;
	while(true)
	{
		char szSendBuf[255] = {0};
		sprintf(szSendBuf, "%s_%d", "ClientSimple", i);
		send(socketSend, szSendBuf, strlen(szSendBuf), 0);

		std::cout<< "Right Send " << szSendBuf << std::endl;
		usleep(500*1000);
		i++;
	}
	close(socketSend);
	
	return 0;
}