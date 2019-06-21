#include "pch.h"

#include <string>
#include <boost/asio.hpp>

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	std::string strIp = TARGET_VALUE_IP;
	int nPort = TARGET_VALUE_PORT;
	boost::asio::ip::tcp::endpoint eps(boost::asio::ip::address::from_string(strIp.c_str()),
		nPort);

	boost::asio::ip::tcp::socket socks(io_service);
	boost::system::error_code errors;
	socks.connect(eps, errors);
	if(errors)
	{
		std::cout<< "Wrong:Try Connect" << std::endl;
		return 1;
	}

	char sz_recv[1024] = {0};
	while(true)
	{
		std::size_t len = socks.read_some(boost::asio::buffer(sz_recv), errors);
		if(errors || len==0)
		{
			std::cout<< "Wrong:Disconnect" << std::endl;
			return 1;
		}

		std::string str_recv(sz_recv, len);
		std::cout << str_recv << std::endl;
	}

	return 0;
}