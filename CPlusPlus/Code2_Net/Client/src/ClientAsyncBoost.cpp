#include "pch.h"

#include "ClientAsyncBoost.h"

ClientASyncBoost::ClientASyncBoost()
{

}

ClientASyncBoost::~ClientASyncBoost()
{

}

void ClientASyncBoost::Connect(const uint32_t& nPort, const std::string& strIp)
{
	boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::address::from_string(strIp.c_str()), nPort);
	boost::asio::ip::tcp::socket socket_(g_io_service);

	boost::asio::deadline_timer deadline_(g_io_service);
	deadline_.expires_from_now(boost::posix::seconds(1));

	socket_.async_connect(endPoint, std::bind(&ClientASyncBoost::Handle_Connect, this));

	g_io_service.run();
}

void ClientASyncBoost::Handle_Connect(const boost::system::error_code&)
{
/* if (!socket_.is_open())
		{
			std::cout << "Connect timed out\n";
 
			start_connect(++endpoint_iter);
		}
		else if (ec)
		{// 其他方面的错误 如服务器没有打开
			std::cout << "Connect error: " << ec.message() << "\n";
 
			socket_.close();
 
			start_connect(++endpoint_iter);
		}
		else
		{// 连接成功
			std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";
 
			start_read();
 
			start_write();// 开始心跳
		}

--------------------- 
作者：li_jian_xing 
来源：CSDN 
原文：https://blog.csdn.net/li_jian_xing/article/details/50394116 
版权声明：本文为博主原创文章，转载请附上博文链接！ */
}

void ClientASyncBoost::Handle_Write(const boost::system::error_code&)
{
/* if (!ec)
		{
			// 设定超时时间
			heartbeat_timer_.expires_from_now(boost::posix_time::seconds(10));
			
			// 开始异步等待，并设定超时回调函数
			heartbeat_timer_.async_wait(boost::bind(&client::start_write, this));
		}
		else
		{
			std::cout << "Error on heartbeat: " << ec.message() << "\n";
 
			stop();
		}

--------------------- 
作者：li_jian_xing 
来源：CSDN 
原文：https://blog.csdn.net/li_jian_xing/article/details/50394116 
版权声明：本文为博主原创文章，转载请附上博文链接！ */
}