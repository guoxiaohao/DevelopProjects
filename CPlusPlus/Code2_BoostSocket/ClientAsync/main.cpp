#include "pch.h"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <vector>

class clients
{
public:
	clients(boost::asio::io_service* io_services, std::string str_address,int nport,int id_val)
		:m_ios(io_services),
		m_ep(boost::asio::ip::address::from_string(str_address.c_str()), nport),
		_id(id_val)
	{
		start();
	}

	void start()
	{
		boost::shared_ptr<boost::asio::ip::tcp::socket>sock(new boost::asio::ip::tcp::socket(*m_ios));
		sock->async_connect(m_ep,boost::bind(&clients::conn_handler, this, boost::asio::placeholders::error, sock));
	}

	void conn_handler(const boost::system::error_code& ec, boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
	{
		if(ec)
		{
			std::cout << "id: " << _id << " connect wrong" << std::endl;
			return;
		}

		std::cout << "id: " << _id << " connect right to address:" << sock->remote_endpoint().address() << std::endl;
		sendtimer_=std::make_shared<boost::asio::deadline_timer>(*m_ios);
		
		sendtimer_->expires_from_now(boost::posix_time::milliseconds(500));
		sendtimer_->async_wait(boost::bind(&clients::do_write, this, sock));
	}

	void do_write(boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
	{
		char sz_send[512]={0};
		sprintf(sz_send,"%d_hello",_id);

		m_buf.clear();
		for(int i=0; i<strlen(sz_send); i++)
		{
			m_buf.push_back(sz_send[i]);
		}

		sock->async_write_some(boost::asio::buffer(m_buf), boost::bind(&clients::write_handler, this,boost::asio::placeholders::error, sock));
	}

	void write_handler(const boost::system::error_code& ec,boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
	{
		if(ec)
		{
			std::cout << "id: " << _id <<" connect disconnect" << std::endl;
		}
		else
		{
			sendtimer_->expires_from_now(boost::posix_time::milliseconds(500));
			sendtimer_->async_wait(boost::bind(&clients::do_write, this, sock));
		}
	}
private:
	boost::asio::io_service* m_ios;
	boost::asio::ip::tcp::endpoint m_ep;
	int _id;
	std::vector<char> m_buf;
	std::shared_ptr<boost::asio::deadline_timer> sendtimer_;
};

int main(int argc, char** argv)
{
	int id_val = 0;
	if(argc>1)
	{
		char* ch_val = argv[1];
		id_val = atoi(ch_val);
	}

	int nport = TARGET_VALUE_PORT;
	std::string str_address = TARGET_VALUE_IP;
	std::cout << "id: " << id_val << " client start" << std::endl;

	boost::asio::io_service io_servoces;
	clients cl(&io_servoces, str_address, nport, id_val);
	io_servoces.run();

	std::cout << "id: " << id_val << " client end" << std::endl;

	return 0;
}