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
        case 1:
            {

            }
            break;
        default:
            {
                ClientSync cli;
                std::thread threadCi(&ClientSync::Connect, 
                    &cli, nPort, strIp);
                threadCi.join(); 
            }
            break;
    }

    return 0;
}
