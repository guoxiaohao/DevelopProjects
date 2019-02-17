#include "pch.h"

#include <math.h>

#include <vector>
#include <thread>
#include <functional>

#include "boost/asio.hpp"

boost::asio::io_service boostIoService;

void MyPrint1(const boost::system::error_code)
{
	std::cout << "Anys End Wait" << std::endl;
}
typedef std::function <void(const boost::system::error_code&)> Timer_CB;

int main(int argc, char** argv)
{
    std::vector<int> vecInts;
    vecInts.clear();
    vecInts.push_back(4);vecInts.push_back(25);vecInts.push_back(36);

    std::thread t([&]()
    {
        for(int i = 0; i < vecInts.size(); i++)
        {
#if defined(__GNUC__) || defined(__GNUG__)
    sleep(1);
#else
	Sleep(1);
#endif
            std::cout << sqrt(vecInts[i]) << std::endl;
        }
        
    });
    t.join();

	std::cout << "Boost Timer" << std::endl;
	boost::asio::deadline_timer boostDeadtimer(boostIoService, boost::posix_time::seconds(2));
	boostDeadtimer.wait();
	std::cout << "It's Time Wait..." << std::endl;

	boost::asio::deadline_timer boostDeadtimer1(boostIoService, boost::posix_time::seconds(2));
	boostDeadtimer1.async_wait(&MyPrint1);

    std::cout << "Anys Begin Wait" << std::endl;
	boostIoService.run();

    boost::asio::deadline_timer boostDeadtimer2(boostIoService, boost::posix_time::seconds(2));
    Timer_CB call_back_func = [&](const boost::system::error_code& errs){
            std::cout << "Timer Loops" << std::endl;
            boostDeadtimer2.async_wait(call_back_func);
            boostIoService.run();
        };
    std::cout << "Timer Loop Begin" << std::endl;
    boostDeadtimer2.async_wait(call_back_func);
    boostIoService.run();

    std::cout << "Program Ends" << std::endl;
#if defined(__GNUC__) || defined(__GNUG__)
#else
	system("pause");
#endif

    return 0;
}