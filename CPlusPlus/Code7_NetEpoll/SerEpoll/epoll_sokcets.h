#pragma once

#include <mutex>
#include <map>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <sys/epoll.h>

#include "my_connection.h"

struct MySokcets
{
	std::shared_ptr<my_connection> lp;
	struct epoll_event events;
};

class epoll_sokcets
{
public:
	epoll_sokcets(boost::asio::io_service* ios,
		int nums = 64, int inter_timer = 10);
	~epoll_sokcets();
public:
	void Start();
	void add_sockets(int fd_socket, std::shared_ptr<my_connection> lp);
protected:
	void End();
	void recv_data();

	boost::asio::io_service* p_io;
	std::shared_ptr<boost::asio::deadline_timer> startimer_;

	const int inter_timer_;
	const int listen_num_;
	int epoll_handle;

	std::mutex mutex_;
	char sz_recv_buff[4096];

	std::map<int, MySokcets> m_map_;
	std::map<int, MySokcets>::iterator iters_;
};