#include "pch.h"

#include "datas_recv.h"
#include "proto_dir/common_pack_proto.h"

DataRecv::DataRecv()
{
}

DataRecv::~DataRecv()
{
}

void DataRecv::DataRecvFunction1(std::string& strcontent)
{
	server2client::msg_content content;
	content.ParseFromString(strcontent);
	
	if(content.type()!=server2client::msg_connect::id)
	{
		std::cout << "type msg_connect wrong" << std::endl;
		return;
	}
	
	std::cout << "type msg_connect right " << content.type() << std::endl;
	server2client::msg_connect connects;
	std::string tmpstring = content.datas();
	connects.ParseFromString(tmpstring);
	
	if(connects.arr_ints_size()==0)
	{
		std::cout << "param volum is 0" << std::endl;
	}
	else
	{
		for(int i=0; i<connects.arr_ints_size(); i++)
		{
			std::cout << connects.arr_ints(i) << std::endl;
		}
	}
	if(connects.arr_strings_size()==0)
	{
		std::cout << "param volum is 0" << std::endl;
	}
	else
	{
		for(int i=0; i<connects.arr_strings_size(); i++)
		{
			std::cout << connects.arr_strings(i) << std::endl;
		}
	}
}

void DataRecv::DataRecvFunction2(std::string& strcontent)
{
	server2client::msg_content content;
	content.ParseFromString(strcontent);
	
	if(content.type()==server2client::msg_testmap::id)
	{
		std::cout << "type msg_testmap right " << content.type() << std::endl;
	}
	else
	{
		std::cout << "type msg_testmap wrong" << std::endl;
	}
}