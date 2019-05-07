#include "pch.h"

#include "socket_listen.h"

int main(int argc, char** argv)
{
	Socket_Listen socket_listen;
	socket_listen.start(TARGET_VALUE_PORT);

	return 0;
}