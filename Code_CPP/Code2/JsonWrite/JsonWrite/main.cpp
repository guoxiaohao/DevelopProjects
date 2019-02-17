#include "pch.h"

#include <fstream>
#include "json/json.h"

int main(int argc, char** argv)
{
#ifdef MACRO_PREDEFINE_WRITE
	std::cout << "Right Macro" << std::endl;
#endif

	std::fstream fileStream;
	fileStream.open("Test.json", std::ios::out|std::ios::ate|std::ios::app);

	if (fileStream.is_open())
	{
		Json::Value jsonValue;
		Json::FastWriter jsonFastWrite;
		jsonValue["name"] = "guoxh";
		jsonValue["sex"] = "female";
		jsonValue["age"] = "19891012";

		fileStream << jsonFastWrite.write(jsonValue);
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