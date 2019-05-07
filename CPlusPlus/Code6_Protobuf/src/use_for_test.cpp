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
	//code msg_connect
	char datas1[1024] = {0};
	
	server2client::msg_content content;
	content.set_type(server2client::msg_content_msg_type_connect);
	
	char szdata2[1024] = {0};
	server2client::msg_connect connects;
	connects.clear_arr_ints();
	connects.clear_arr_strings();
	connects.add_arr_ints(5);
	connects.add_arr_ints(20);
	connects.add_arr_strings("guoxh");
	connects.add_arr_strings("123456");
	connects.SerializeToArray(szdata2, connects.ByteSize());
	std::string tmpstring(szdata2, connects.ByteSize());
	
	content.set_datas(tmpstring);
	content.SerializeToArray(datas1, content.ByteSize());
	
	std::string buffString(datas1, content.ByteSize());
	if(funca)
	{
		funca(buffString, funcb);
	}
}

void UseForTest::generateDatas2(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb)
{
	//code msg_testmap
	char datas1[1024] = {0};
	
	server2client::msg_content content;
	content.set_type(server2client::msg_content_msg_type_testmap);
	
	content.SerializeToArray(datas1, content.ByteSize());
	
	std::string buffString(datas1, content.ByteSize());
	if(funca)
	{
		funca(buffString, funcb);
	}
}