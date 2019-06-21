#include "pch.h"

#include "my_server_listen.h"

servers::servers(int nport):
	m_acceptor(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), nport)),
	m_sockets(&m_io)
{
	m_sockets.Start();
	accept();
}

servers::~servers()
{
}

void servers::run()
{
	m_io.run();
}

void servers::accept()
{
	std::cout << "prepare accept" << std::endl;

	std::shared_ptr<my_connection> lp = std::make_shared<my_connection>(&m_io);
	m_acceptor.async_accept(lp->Socks(), boost::bind(&servers::accept_handler, this,
		boost::asio::placeholders::error, lp));
}

void servers::accept_handler(const boost::system::error_code& ec, std::shared_ptr<my_connection> lp)
{
	if(ec)
	{
		return;
	}

	std::cout<< "listen the address:" << lp->Socks().remote_endpoint().address() << std::endl;
	m_sockets.add_sockets(lp->Socks().native_handle(), lp);

	accept();
}