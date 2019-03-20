#include "pch.h"

#include "Server1.h"

int main(int argc, char** argv)
{
    uint32_t nPort = TARGET_VALUE_PORT;

    CServer1 ser1;
    ser1.StartUp(nPort);
    
    return 0;
}
