#include "pch.h"

#include "use_for_test.h"
#include "server2client.pb.h"

UseForTest::UseForTest()
{
}

UseForTest::~UseForTest()
{
}

int UseForTest::add(int a, int b)
{
	return a+b;
}

bool UseForTest::getIpInfo()
{
	std::vector<std::string> vec_strings;
	vec_strings.push_back("eth");vec_strings.push_back("em");vec_strings.push_back("oct");
	
	return true;
}

bool UseForTest::compareStructs()
{
	int ttypes = 1;
	std::string tcommand_type = "ABCD";
	server2client tSerCliTmp;
	char datas[1024] = {0};
	
	tSerCliTmp.set_type(ttypes);
	tSerCliTmp.set_command_type(tcommand_type);
	tSerCliTmp.SerializeToString(datas);
	
	return true;
}