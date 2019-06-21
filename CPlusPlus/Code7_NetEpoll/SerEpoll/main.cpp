#include "pch.h"

#include "my_server_listen.h"

int main(int argc, char** argv)
{
	int nport = LISTEN_VALUE_PORT;

	servers srv(nport);
	srv.run();

	return 0;
}