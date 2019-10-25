#include "pch.h"

#include "test_structs.h"

int main(int argc, char** argv)
{
	MYTEST1 mytest1;
	mytest1.data_str = "555";
	mytest1.data_int = 666;
	std::cout << mytest1.struct2string() << std::endl;

	std::cout << "Exit" << std::endl;
	return 0;
}