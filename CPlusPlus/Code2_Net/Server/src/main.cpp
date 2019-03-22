#include "pch.h"

#include "ServerSync.h"
#include "ServerSyncBoost.h"
#include "ServerSelect.h"

int main(int argc, char** argv)
{
    char nTypes = 0;
    uint32_t nPort = TARGET_VALUE_PORT;

    if(argc==2)
    {
        nTypes = *(argv[1]);
    }

    switch (nTypes)
    {
        case '1':
            {
                ServerSyncBoost ser;
                ser.StartUp(nPort);
            }
            break;
        case '2':
            {
                ServerSelect ser;
                ser.StartUp(nPort);
            }
            break;
        default:
            {
                ServerSync ser;
                ser.StartUp(nPort);
            }
            break;
    }
    
    return 0;
}
