#include "pch.h"

#include "my_connection.h"

my_connection::my_connection(boost::asio::io_service* io_service)
	:socket_(*io_service)
{
}

my_connection::~my_connection()
{
}

void my_connection::OnMessage(const std::string& str_msg)
{
	std::cout << str_msg << std::endl;
}

boost::asio::ip::tcp::socket& my_connection::Socks()
{
	return socket_;
}