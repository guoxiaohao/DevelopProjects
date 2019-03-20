#include "pch.h"

#include "ClientSync.h"

ClientSync::ClientSync()
{
}

ClientSync::~ClientSync()
{

}

void ClientSync::Connect(const uint32_t& nPort, const std::string& strIp)
{
    struct sockaddr_in addrSend;

    memset(&addrSend, 0, sizeof(addrSend));
    addrSend.sin_family = AF_INET;
    addrSend.sin_port = htons(TARGET_VALUE_PORT);
    addrSend.sin_addr.s_addr = inet_addr(TARGET_VALUE_IP);

    int socketSend = socket(AF_INET, SOCK_STREAM, 0);
    if(socketSend<0)
    {
        std::cout << "Wrong - Client Init Socket" << std::endl;
        return;
    }

    while(connect(socketSend, (struct sockaddr*)&addrSend, sizeof(addrSend))!=0);
    std::cout << "Right - Client Connect " << std::endl;

    int i = 0;
    while(true)
    {
        char szSendBuf[255] = {0};
        sprintf(szSendBuf, "%s_%d", "Send", i);
        int nRet = send(socketSend, szSendBuf, strlen(szSendBuf)+1, 0);

        if(nRet<0)
        {
            std::cout << "Wrong " << szSendBuf << std::endl;
            break;
        }
        else
        {
            std::cout<< "Right " << szSendBuf << std::endl;
        }
        usleep(500*1000);
        i++;
    }
    close(socketSend);

    std::cout << "Client Quit Stop" << std::endl;                     
}
