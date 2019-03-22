#include "pch.h"

#include "ClientSync.h"
#include "ClientSyncBoost.h"

int main(int argc, char** argv)
{
    char nTypes = 0;
    uint32_t nPort = TARGET_VALUE_PORT;
    std::string strIp = TARGET_VALUE_IP;

    if(argc==2)
    {
        nTypes = *(argv[1]);
    }
    
    switch (nTypes)
    {
        case '1':
            {
                ClientSyncBoost cli;
                std::thread threadCli(&ClientSyncBoost::Connect, &cli, std::ref(nPort), std::ref(strIp));
                threadCli.join();
            }
            break;
        default:
            {
                ClientSync cli;
                std::thread threadCli(&ClientSync::Connect, &cli, std::ref(nPort), std::ref(strIp));
                threadCli.join(); 
            }
            break;
    }

    return 0;
}
