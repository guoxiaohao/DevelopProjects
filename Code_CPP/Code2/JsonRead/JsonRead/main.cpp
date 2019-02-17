#include "pch.h"

#include <fstream>
#include "json/json.h"

int main(int argc, char** argv)
{
#ifdef MACRO_PREDEFINE_READ
	std::cout << "Right Macro" << std::endl;
#endif

	std::fstream fileStream;
	fileStream.open("Test.json", std::ios::in);
	if (fileStream.is_open())
	{
		Json::Value jsonValue;
		Json::Reader jsonRead;
		if (jsonRead.parse(fileStream, jsonValue))
		{
			std::cout << jsonValue["name"].asString() << std::endl;
			std::cout << jsonValue["age"].asString() << std::endl;
		}
		fileStream.close();
	}
	else
	{
		std::cout << "Wrong Open File" << std::endl;
	}

#if defined(__GNUC__) || defined(__GNUG__)
	pause();
#else
	system("pause");
#endif

    return 0;
}