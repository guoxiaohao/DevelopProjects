#include "pch.h"

#include <string.h>
#include "client_use.h"

void ConnectorImpl::Release()
{
	delete this;
}

void ConnectorImpl::RegisterSpi(ConnectorSpi* spi)
{
	spi_ = spi;
}

void ConnectorImpl::Connect(std::string& ip, int port)
{
	deadline_timers = std::make_shared<boost::asio::deadline_timer>(io_service_);

	deadline_timers->expires_from_now(boost::posix_time::milliseconds(100)); 
	deadline_timers->async_wait(boost::bind(&ConnectorImpl::do_connect, this, std::ref(ip), port));
}

void ConnectorImpl::SendMessage(std::string msg)
{
	deadline_timers->expires_from_now(boost::posix_time::milliseconds(100)); 
	deadline_timers->async_wait(boost::bind(&ConnectorImpl::do_send, this, msg));
}

void ConnectorImpl::EnableWorkThread()
{
	bLoop = true;
}

void ConnectorImpl::DoWorkThread()
{
	if(bLoop)
	{
		io_service_.run();
	}
}

void ConnectorImpl::do_connect(std::string& ip, int port)
{
	std::cout << "prepare connect:ip," << ip <<" port," << port << std::endl;
	struct sockaddr_in addrSend;
	memset(&addrSend, 0, sizeof(addrSend));
	addrSend.sin_family = AF_INET;
	addrSend.sin_port = htons(port);
	addrSend.sin_addr.s_addr = inet_addr(ip.c_str());

	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if( connect(socket_, (struct sockaddr*)&addrSend, sizeof(addrSend))!=0 )
	{
		spi_->OnConnected(1);
	}
	else
	{
		spi_->OnConnected(0);
	}
}

void ConnectorImpl::do_send(std::string msg)
{
	std::cout << "prepare send:" << msg << std::endl;
	int i = 0;
	while(true)
	{
		char szSendBuf[255] = {0};
		sprintf(szSendBuf, "%s_%d", msg.c_str(), i);
		send(socket_, szSendBuf, strlen(szSendBuf), 0);
		std::cout<< "Right Send " << szSendBuf << std::endl;
		usleep(500*1000);
		i++;
	}
	close(socket_);
}

Connector* CreateConnectorObj()
{
	return new ConnectorImpl();
}

ClientSpi::ClientSpi()
{
	connector_ = CreateConnectorObj();
}

ClientSpi::~ClientSpi()
{
	connector_->Release();
}

void ClientSpi::Start()
{
	str_ip_ = TARGET_VALUE_IP;
	nport_ = TARGET_VALUE_PORT;

	connector_->EnableWorkThread();
	connector_->RegisterSpi(this);
	connector_->Connect(str_ip_, nport_);
	connector_->DoWorkThread();
}

void ClientSpi::OnConnected(int result)
{
	if(result==0)
	{
		std::cout << "Success" << std::endl;
		connector_->SendMessage("guoxh client simple");
	}
	else
	{
		std::cout << "Failed" << std::endl;
	}
}

void ClientSpi::OnDisconnected()
{
}

void ClientSpi::OnMessage(std::string msg)
{
}