#include "pch.h"

#include "use_for_test.h"
#include "proto_dir/common_pack_proto.h"

UseForTest::UseForTest()
{
}

UseForTest::~UseForTest()
{
}

void UseForTest::generateDatas1(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb)
{
	//code msg_connect
	server2client::msg_connect connects;
	connects.clear_arr_ints();
	connects.clear_arr_strings();
	connects.add_arr_ints(5);
	connects.add_arr_ints(20);
	connects.add_arr_strings("guoxh");
	connects.add_arr_strings("123456");
	std::string buffString = MsgContent_proto(connects);

	if(funca)
	{
		funca(buffString, funcb);
	}
}

void UseForTest::generateDatas2(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb)
{
	//code msg_testmap
	server2client::msg_testmap testmaps;
	std::string buffString = MsgContent_proto(testmaps);

	if(funca)
	{
		funca(buffString, funcb);
	}
}