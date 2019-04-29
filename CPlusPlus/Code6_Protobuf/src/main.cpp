#include "pch.h"

#include <functional>

#include "use_for_test.h"
#include "datas_send.h"
#include "datas_recv.h"

int main(int argc, char** argv)
{
	UseForTest usefortest;
	DataSend datasend;
	DataRecv datarecv;
	
	usefortest.generateDatas1(std::bind(&DataSend::DataSendFunction1, &datasend, std::placeholders::_1, std::placeholders::_2),
					std::bind(&DataRecv::DataRecvFunction1, &datarecv, std::placeholders::_1));
	usefortest.generateDatas2(std::bind(&DataSend::DataSendFunction2, &datasend, std::placeholders::_1, std::placeholders::_2),
					std::bind(&DataRecv::DataRecvFunction2, &datarecv, std::placeholders::_1));
	
	return 0;
}