#include "pch.h"

#include <string>
#include <memory>
#include <thread>
#include <boost/asio.hpp> 

void thread_socket(std::shared_ptr<boost::asio::ip::tcp::socket> lp);

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	int nport = LISTEN_VALUE_PORT;
	boost::asio::ip::tcp::acceptor acceptors(io_service, 
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), nport));

	
	while(true)
	{
		std::shared_ptr<boost::asio::ip::tcp::socket> lpsocket = 
			std::make_shared<boost::asio::ip::tcp::socket>(io_service);

		boost::system::error_code errors;
		acceptors.accept(*lpsocket, errors);

		if(errors)
		{
			std::cout << "Error" << std::endl;
			return 1;
		}
		else
		{
			std::thread threadsockets(thread_socket, lpsocket);
			threadsockets.detach();
		}
	}

	return 0;
}

void thread_socket(std::shared_ptr<boost::asio::ip::tcp::socket> lp)
{
	while(true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		lp->write_some(boost::asio::buffer("hello world!"));
	}
}