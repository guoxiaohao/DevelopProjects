#pragma once

#include <functional>

class UseForTest
{
public:
	UseForTest();
	~UseForTest();
public:
	void generateDatas1(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb);
	void generateDatas2(std::function<void(std::string&, std::function<void(std::string&)>)> funca, std::function<void(std::string&)> funcb);
};