#include "pch.h"

#include "ServerSyncBoost.h"

ServerSyncBoost::ServerSyncBoost()
{

}

ServerSyncBoost::~ServerSyncBoost()
{

}

void ServerSyncBoost::StartUp(const uint32_t& nPort)
{
    boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::tcp::v4(), nPort);
    boost::asio::ip::tcp::acceptor socketListen(g_io_service, endPoint);
    std::shared_ptr<boost::asio::ip::tcp::socket> lpSharedSocketAccept =
		std::make_shared< boost::asio::ip::tcp::socket>(g_io_service);
	
    std::cout << "ServerSyncBoost Wait for ..." << std::endl;
	socketListen.accept(*lpSharedSocketAccept);
    
    std::thread threadSer([&lpSharedSocketAccept](){
        std::cout << "Right ServerSyncBoost Recv Data" << std::endl;

        boost::system::error_code ec;
        while (true)
        {
            char szRecvBuff[512] = { 0 };
            int len = lpSharedSocketAccept->read_some(boost::asio::buffer(szRecvBuff), ec);
            if (len>0)
            {
                std::cout << szRecvBuff << std::endl;
            }
            else
            {
                break;
            }
        }
    });

    threadSer.join();
    std::cout << "ServerSyncBoost End" << std::endl;

    lpSharedSocketAccept->close();
}
