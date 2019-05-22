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

void ConnectorImpl::SendMessage(const std::string& msg)
{
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

void ConnectorImpl::RecvMessage()
{
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

	connector_->RegisterSpi(this);
	connector_->Connect(str_ip_, nport_);
}

void ClientSpi::OnConnected(int result)
{
	if(result==0)
	{
		std::cout << "Failed Success" << std::endl;
		connector_->SendMessage("guoxh client simple");
	}
	else
	{
		std::cout << "Failed Connect" << std::endl;
	}
}

void ClientSpi::OnDisconnected()
{
}

void ClientSpi::OnMessage(std::string msg)
{
}