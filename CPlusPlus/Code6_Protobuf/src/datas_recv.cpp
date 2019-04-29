#include "pch.h"

#include "datas_recv.h"
#include "server2client.pb.h"

DataRecv::DataRecv()
{
}

DataRecv::~DataRecv()
{
}

void DataRecv::DataRecvFunction1(std::string& strcontent)
{
	server2client::msg_head head2;
	server2client::msg_connect connect2;
	
	char sz_data[1024] = {0};
	memcpy(sz_data, strcontent.c_str(), strcontent.length());
	
	head2.ParseFromString(sz_data);
	connect2.ParseFromArray(sz_data+strcontent.length()-head2.bytes_msg(), head2.bytes_msg());
	
	std::cout << head2.bytes_msg() << std::endl;
	if(connect2.arr_ints_size()==0)
	{
		std::cout << "param volum is 0" << std::endl;
	}
	else
	{
		for(int i=0; i<connect2.arr_ints_size(); i++)
		{
			std::cout << connect2.arr_ints(i) << std::endl;
		}
	}
	if(connect2.arr_strings_size()==0)
	{
		std::cout << "param volum is 0" << std::endl;
	}
	else
	{
		for(int i=0; i<connect2.arr_strings_size(); i++)
		{
			std::cout << connect2.arr_strings(i) << std::endl;
		}
	}
}

void DataRecv::DataRecvFunction2(std::string& strcontent)
{
}