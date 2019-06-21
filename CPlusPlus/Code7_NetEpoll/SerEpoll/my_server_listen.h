#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include "epoll_sokcets.h"
#include "my_connection.h"

class servers
{
public:
	servers(int nport);
	~servers();

	void run();
protected:
	void accept();

	void accept_handler(const boost::system::error_code& ec,
		std::shared_ptr<my_connection> lp);
private:
	boost::asio::io_service m_io;
	boost::asio::ip::tcp::acceptor m_acceptor;
	epoll_sokcets  m_sockets;
};