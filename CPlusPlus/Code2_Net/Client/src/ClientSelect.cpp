#include "pch.h"

#include "ClientSelect.h"

ClientSelect::ClientSelect()
{
    bLoop = true;
}

ClientSelect::~ClientSelect()
{

}

 void ClientSelect::Connect(const uint32_t& nPort, const std::string& strIp)
 {
    struct sockaddr_in addrSend;

    memset(&addrSend, 0, sizeof(addrSend));
    addrSend.sin_family = AF_INET;
    addrSend.sin_port = htons(TARGET_VALUE_PORT);
    addrSend.sin_addr.s_addr = inet_addr(TARGET_VALUE_IP);

    int socketSend = socket(AF_INET, SOCK_STREAM, 0);
    if(socketSend<0)
    {
        std::cout << "Wrong - ClientSelect Init Socket" << std::endl;
        return;
    }

    int options = fcntl(socketSend, F_GETFL, 0);
    fcntl(socketSend, F_SETFL, options | O_NONBLOCK);
    fd_set writeFdSet;  
    int socketMax = socketSend;
    timeval timeout;

    int nRet = connect(socketSend, (struct sockaddr*)&addrSend, sizeof(addrSend));
    if(nRet==0)
    {
        std::cout << "Right - ClientSelect Connect " << std::endl;
    }
    else
    {
        if(errno == EINPROGRESS)
        {
            while(bLoop)
            {
                timeout.tv_sec=0;
                timeout.tv_usec=200;

        FD_ZERO(&writeFdSet);
        FD_SET(socketSend, &writeFdSet);
        int nRets = select(socketMax+1, NULL, &writeFdSet, NULL, &timeout);
        if(nRets<0)
        {
            break;
        }
        else if(nRets==0)
        {
            continue;
        }
        else
        {
            if(FD_ISSET(socketSend, &writeFdSet))
            {
                int error;
                socklen_t errlen;
                if( getsockopt(socketSend, SOL_SOCKET, SO_ERROR, &error, &errlen) <0)
                {
                    error = 1;
                }
                if(error==0)
                {
                    std::cout << "Right - ClientSelect Connect " << std::endl;
                    bLoop = false;
                }
            }
        }
    }

        }
    }

    int i = 0;
    while(true)
    {
        char szSendBuf[255] = {0};
        sprintf(szSendBuf, "%s_%d", "ClientSelectSend", i);
        send(socketSend, szSendBuf, strlen(szSendBuf)+1, 0);
        std::cout<< "Right Send " << szSendBuf << std::endl;
        usleep(500*1000);
        i++;
    }
    close(socketSend);

    std::cout << "ClientSync Quit Stop" << std::endl;
 }