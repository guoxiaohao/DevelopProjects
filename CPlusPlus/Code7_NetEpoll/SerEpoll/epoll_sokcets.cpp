#include "pch.h"

#include "epoll_sokcets.h"

epoll_sokcets::epoll_sokcets(boost::asio::io_service* ios, int nums, int inter_timer):
	p_io(ios), listen_num_(nums), inter_timer_(inter_timer)
{
}

epoll_sokcets::~epoll_sokcets()
{
	End();
	if(epoll_handle>0)
	{
		close(epoll_handle);
	}
}

void epoll_sokcets::Start()
{
	epoll_handle = epoll_create(listen_num_);

	if(epoll_handle>0)
	{
		startimer_ = std::make_shared<boost::asio::deadline_timer>(*p_io);
		startimer_->expires_from_now(boost::posix_time::milliseconds(inter_timer_));
		startimer_->async_wait(boost::bind(&epoll_sokcets::recv_data, this));
	}
}

void epoll_sokcets::add_sockets(int fd_socket, std::shared_ptr<my_connection> lp)
{
	std::lock_guard<std::mutex> locks_(mutex_);

	if(epoll_handle>0)
	{
		MySokcets tmpStruct;
		tmpStruct.lp = lp;
		tmpStruct.events.data.fd = fd_socket;
		tmpStruct.events.events = EPOLLIN;

		epoll_ctl(epoll_handle, EPOLL_CTL_ADD, fd_socket, &tmpStruct.events);
		m_map_.insert(std::pair<int, MySokcets>(fd_socket, tmpStruct));
	}
}

void epoll_sokcets::End()
{
	if(m_map_.size()>0)
	{
		for(iters_=m_map_.begin(); iters_!=m_map_.end();)
		{
			m_map_.erase(iters_++);
		}
	}
}

void epoll_sokcets::recv_data()
{
	if(epoll_handle>0 && m_map_.size()>0)
	{
		int max_fd_ = 0;
		for(iters_=m_map_.begin(); iters_!=m_map_.end(); iters_++)
		{
			if(iters_->second.events.data.fd>max_fd_)
			{
				max_fd_ = iters_->second.events.data.fd;
			}
		}

		struct epoll_event events[64];
		int nret = epoll_wait(epoll_handle, events, max_fd_, 10);
		for(int i=0; i<nret; i++)
		{
			if(events[i].events&EPOLLIN)
			{
				int nlen = recv(events[i].data.fd, sz_recv_buff, sizeof(sz_recv_buff), 0);
				if(nlen>0)
				{
					std::string str_recv(sz_recv_buff, nlen);
					iters_ = m_map_.find(events[i].data.fd);
					if(iters_!=m_map_.end())
					{
						iters_->second.lp->OnMessage(str_recv);
					}
				}
				else
				{
					int fd_del = events[i].data.fd;
					iters_ = m_map_.find(events[i].data.fd);
					if(iters_!=m_map_.end())
					{
						std::cout << fd_del << " the socket closed" << std::endl;
						m_map_.erase(iters_++);
					}
				}
			}
		}
	}

	startimer_->expires_from_now(boost::posix_time::milliseconds(inter_timer_));
	startimer_->async_wait(boost::bind(&epoll_sokcets::recv_data, this));
}