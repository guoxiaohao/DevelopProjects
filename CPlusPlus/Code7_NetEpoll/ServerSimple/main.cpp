#include "pch.h"

#include "server_accept.h"

int main(int argc, char** argv)
{
	ServerSocket servers;
	int nPort = TARGET_VALUE_PORT;
	servers.Start(nPort);

	return 0;
}