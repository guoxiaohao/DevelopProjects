#include "pch.h"

#include <sys/socket.h>



int main(int argc, char** argv)
{
    SOCKET m_sock = socket(AF_INET, SOCK_STREAM, 0);

    return 0;
}