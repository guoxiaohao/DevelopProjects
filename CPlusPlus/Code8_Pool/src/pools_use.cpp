#include "pch.h"

#include <ctime>
#include "time.h"
#include "pools_use.h"
#include "my_threadpool.h"
#include "my_memorypool.h"

std::string get_time()
{
	time_t time_now;
	time(&time_now);
	char sz_time[64];
	strftime(sz_time, sizeof(sz_time), "%Y-%m-%d %H:%M:%S", localtime(&time_now));

	return sz_time;
}

void thread_pool_for()
{
	std::string str_time = get_time();
	std::cout << "A--start thread_pool: " << str_time << std::endl;
	int arr_int[100];

	double time_start, time_end;
	time_start = clock();
	for(int i=0; i<100; i++)
	{
		MyThread<int> my_thread_;
		my_thread_.Run();
		for(int j=0; j<100; j++)
		{
			arr_int[j] = j;
			my_thread_.Post(&arr_int[j]);
		}
		my_thread_.End_Join();
		my_thread_.Release();
	}
	time_end = clock();
	std::cout << "single thread time: "<< std::minus<double>()(time_end, time_start) << std::endl;

	time_start = clock();
	for(int i=0; i<100; i++)
	{
		MyThreadPool<int> my_threadpool_;
		my_threadpool_.Init(4);
		my_threadpool_.Run();
		for(int j=0; j<100; j++)
		{
			arr_int[j] = j;
			my_threadpool_.Post(&arr_int[j]);
		}
		my_threadpool_.JoinExit();
	}
	time_end = clock();
	std::cout << "thread pool time: "<< std::minus<double>()(time_end, time_start) << std::endl;
}

void memory_pool_for()
{
	std::string str_time = get_time();
	std::cout << "B--start memory_pool: " << str_time << std::endl;

	int* arr_int[1000];
	double time_start, time_end;
	time_start = clock();
	for(int i=0; i<10000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			arr_int[j] = new int(j);
		}
		for(int j=0; j<1000; j++)
		{
			delete arr_int[j];
		}
	}
	time_end = clock();
	std::cout << "simple memeory time: "<< std::minus<double>()(time_end, time_start) << std::endl;

	MyMemoPool<int, 100> memo_pools;
	int* arr_ret[1000];
	time_start = clock();
	for(int i=0; i<10000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			arr_ret[j] = memo_pools.my_construct(j);
		}
		for(int j=0; j<1000; j++)
		{
			memo_pools.my_disconstruct(arr_ret[j]);
		}
	}
	time_end = clock();
	std::cout << "memeory pool time: "<< std::minus<double>()(time_end, time_start) << std::endl;
}