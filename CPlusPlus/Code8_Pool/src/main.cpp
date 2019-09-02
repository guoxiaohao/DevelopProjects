#include "pch.h"

#include <time.h>
#include <thread>
#include "pools_use.h"

int main(int argc, char** argv)
{
	//thread_pool_for();
	//std::this_thread::sleep_for( std::chrono::seconds(1) );
	//memory_pool_for();

	struct guoxh1
	{
		char szdata[40];
		int val;
	};
	struct guoxh2
	{
		char szdata[40];
		int val;
	} __attribute__((aligned(64)));
	struct timespec time_start={0, 0}, time_end={0, 0};
	{
		clock_gettime(CLOCK_REALTIME, &time_start);
		guoxh1 a, b, c;
		a.val = 1;
		b.val = 2;
		c.val = 3;
		clock_gettime(CLOCK_REALTIME, &time_end);
	}
	std::cout << " sec:" << time_end.tv_sec - time_start.tv_sec << " nsec:" << time_end.tv_nsec - time_start.tv_nsec << std::endl;

	{
		clock_gettime(CLOCK_REALTIME, &time_start);
		guoxh2 a, b, c;
		a.val = 1;
		b.val = 2;
		c.val = 3;
		clock_gettime(CLOCK_REALTIME, &time_end);
	}
	std::cout << " sec:" << time_end.tv_sec - time_start.tv_sec << " nsec:" << time_end.tv_nsec - time_start.tv_nsec << std::endl;

	return 0;
}