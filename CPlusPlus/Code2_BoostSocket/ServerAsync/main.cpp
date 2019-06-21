#include "pch.h"

#include <boost/asio.hpp> 
#include <boost/bind/bind.hpp>

class servers
{
public:
	servers(boost::asio::io_service* io_ser, int nport):
		m_acceptor(*io_ser, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), nport))
	{
		accept();
	}

	void accept()
	{
		std::cout << "prepare accept" << std::endl;

		boost::shared_ptr<boost::asio::ip::tcp::socket> sock( new boost::asio::ip::tcp::socket(m_acceptor.get_io_service()) );
		m_acceptor.async_accept(*sock, boost::bind(&servers::accept_handler, this, boost::asio::placeholders::error, sock));
	}

	void accept_handler(const boost::system::error_code& ec, boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
	{
		if(ec)
		{
			return;
		}

		std::cout<< sock->remote_endpoint().address() << std::endl;
		sock->async_read_some(boost::asio::buffer(sz_recvdata), boost::bind(&servers::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sock));

		accept();
	}

	void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred, boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
	{
		if(ec || bytes_transferred==0)
		{
			std::cout << "Disconnnect" << std::endl;
			return;
		}

		std::string tmpstr(sz_recvdata, bytes_transferred);
		std::cout << "Recv Data: " << tmpstr << std::endl;

		sock->async_read_some(boost::asio::buffer(sz_recvdata), boost::bind(&servers::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, sock));
	}
private:
	boost::asio::ip::tcp::acceptor m_acceptor;
	char sz_recvdata[1024];
};

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	int nport = LISTEN_VALUE_PORT;
	servers srv(&io_service, nport);
	io_service.run();

	return 0;
}