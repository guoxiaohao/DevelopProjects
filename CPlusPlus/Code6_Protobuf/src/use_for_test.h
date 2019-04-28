#pragma once

#include <vector>
#include <string>

struct InfoStruct
{
	int type;
	std::string commands;
};

class UseForTest
{
public:
	UseForTest();
	~UseForTest();
public:
	int add(int a, int b);
	bool getIpInfo();
	bool compareStructs();
protected:
	InfoStruct m1;
	InfoStruct m2;
};