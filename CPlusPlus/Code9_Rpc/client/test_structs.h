#pragma once

#include <string>
#include <sstream>

struct MYTEST1
{
	std::string data_str;
	int data_int;

	MYTEST1()
	{
		data_str = "";
		data_int = 0;
	}

	std::string struct2string()
	{
		std::ostringstream ostr;
		ostr << "data_str:" << data_str
			 << " data_int:" << data_int;
		return ostr.str();
	}
};