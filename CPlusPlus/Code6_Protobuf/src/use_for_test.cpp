#include "pch.h"

#include "use_for_test.h"
#include "server2client.pb.h"

UseForTest::UseForTest()
{
}

UseForTest::~UseForTest()
{
}

void UseForTest::generateDatas1(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb)
{
	char datas1[1024] = {0};
	
	server2client::msg_head head1;
	server2client::msg_connect connect1;
	
	head1.set_ntype(server2client::msg_head_msg_type::msg_head_msg_type_connect);
	connect1.clear_arr_ints();
	connect1.add_arr_ints(5);
	connect1.add_arr_ints(20);
	connect1.clear_arr_strings();
	connect1.add_arr_strings("guoxh");
	connect1.add_arr_strings("123456");
	head1.set_bytes_msg(connect1.ByteSize());
	
	head1.SerializeToArray(datas1, head1.ByteSize());
	connect1.SerializeToArray(datas1+head1.ByteSize(), connect1.ByteSize());
	
	std::string buffString(datas1, head1.ByteSize()+connect1.ByteSize());
	if(funca)
	{
		funca(buffString, funcb);
	}
}

void UseForTest::generateDatas2(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb)
{
	//map_info_size()
	char datas2[1024] = {0};
	
	server2client::msg_head head1;
	server2client::msg_testmap testmap1;
	
	head1.set_ntype(server2client::msg_head_msg_type::msg_head_msg_type_testmap);
	testmap1.clear_map_info();
	//testmap1
	head1.set_bytes_msg(testmap1.ByteSize());
	
	head1.SerializeToArray(datas2, head1.ByteSize());
	testmap1.SerializeToArray(datas2+head1.ByteSize(), testmap1.ByteSize());
	
	std::string buffString(datas2, head1.ByteSize()+testmap1.ByteSize());
	if(funca)
	{
		funca(buffString, funcb);
	}
}