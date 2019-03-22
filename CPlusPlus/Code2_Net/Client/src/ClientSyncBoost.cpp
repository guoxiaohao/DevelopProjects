#include "pch.h"

#include "ClientSyncBoost.h"

ClientSyncBoost::ClientSyncBoost()
{

}

ClientSyncBoost::~ClientSyncBoost()
{

}

void ClientSyncBoost::Connect(const uint32_t& nPort, const std::string& strIp)
{
    boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::address::from_string(strIp.c_str()), nPort);
    boost::asio::ip::tcp::socket boost_socket(g_io_service);
    boost::system::error_code ec;

    while (true)
    {
        boost_socket.connect(endPoint, ec);
        if (ec.value() == 0)
        {break;}
    }

    if (!boost_socket.is_open())
    {
        std::cout << "Wrong - ClientSyncBoost Connect" << std::endl;
		return;
    }
    else
    {
        std::cout << "Right - ClientSyncBoost Connect " << std::endl;
    }
    
    int i = 0;
    while(true)
    {
        char szBuffSend[255] = { 0 };
		sprintf(szBuffSend, "%s_%d", "ClientSyncBoostSend", i);
        boost_socket.write_some(boost::asio::buffer(szBuffSend));
        std::cout<< "Right Send " << szBuffSend << std::endl;
        usleep(500*1000);
        i++;
    }
    
	boost_socket.close();

    std::cout << "ClientSyncBoost Quit Stop" << std::endl;   
}
