#include "pch.h"

#include <set>

#include "ServerSelect.h"

ServerSelect::ServerSelect()
{
    bLoop = true;
}

ServerSelect::~ServerSelect()
{

}

void ServerSelect::StartUp(const uint32_t& nPort)
{
    sockaddr_in addrListen;
	memset(&addrListen, 0, sizeof(addrListen));
	addrListen.sin_family = AF_INET;
	addrListen.sin_port = htons(nPort);
	addrListen.sin_addr.s_addr = htonl(INADDR_ANY);
    
	int socketListen = socket(AF_INET, SOCK_STREAM, 0);
	if (socketListen<0)
	{
		std::cout << "Wrong - ServerSelect Init Socket" << std::endl;
		return;
	}

    bind(socketListen, (sockaddr*)&addrListen, sizeof(addrListen));
	listen(socketListen, 5);

    fd_set readSets;  
    int socketMax = socketListen;
    std::set<int> setsockets;
    std::set<int>::iterator iter;
    setsockets.clear();
    setsockets.insert(socketListen);
    timeval timeout;
    std::cout << "ServerSelect Wait for ..." << std::endl;
    int sock_client;

    while(bLoop)
    {
        timeout.tv_sec=0;
        timeout.tv_usec=200;

        FD_ZERO(&readSets);
        std::cout << setsockets.size() << std::endl;
        for(iter=setsockets.begin(); iter!=setsockets.end(); iter++)
        {
            FD_SET(*iter, &readSets);
            if(*iter>socketMax==socketListen)
            {
                socketMax = *iter;
            }
        }

        int nRets = select(socketMax+1, &readSets, NULL, NULL, &timeout);
        if(nRets<0)
        {
            std::cout << "ServerSelect Accept break" << std::endl;
            break;
        }
        else if(nRets==0)
        {
            std::cout << "ServerSelect Accept Continue" << std::endl;
            continue;
        }
        else
        {
            for(iter=setsockets.begin(); iter!=setsockets.end(); iter++)
            {
                if(FD_ISSET(*iter, &readSets)) 
                {
                    if(*iter==socketListen)
                    {
                        std::cout << "ServerSelect Accept New sockets" << std::endl;

                        sockaddr_in client_addr;
                        socklen_t size = sizeof(client_addr);
                        sock_client = accept(socketListen, (sockaddr*)(&client_addr), &size);
                        if(sock_client > 0)
                        {
                            setsockets.insert(sock_client);
                        }
                    }
                    else
                    {
                        char szRecvBuff[512] = { 0 };
                        int len = recv(*iter, szRecvBuff, sizeof(szRecvBuff) - 1, 0);
                        if (len > 0)
                        {
                            std::cout << szRecvBuff << std::endl;
                        }
                        else
                        {
                            close(*iter);
                            setsockets.erase(*iter);
                            if(setsockets.size()==1)
                            {
                                bLoop = false;
                            }
                        }
                    }
                }     
            }
        }//select FDSET有数据
    }// 监听

    close(socketListen);
}