#include "pch.h"

#include <thread>
#include "pools_use.h"

int main(int argc, char** argv)
{
	thread_pool_for();
	std::this_thread::sleep_for( std::chrono::seconds(1) );
	memory_pool_for();

	return 0;
}