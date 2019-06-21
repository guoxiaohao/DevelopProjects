#pragma once

#include <boost/asio.hpp>

class my_connection
{
public:
	my_connection(boost::asio::io_service* io_service);
	~my_connection();

	void OnMessage(const std::string& str_msg);
	boost::asio::ip::tcp::socket& Socks();
protected:
	boost::asio::ip::tcp::socket socket_;
};