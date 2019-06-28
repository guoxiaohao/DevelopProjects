#pragma once

#include <thread>
#include <mutex>
#include <deque>
#include <vector>

template<typename T>
class MyThread
{
public:
	void Run()
	{
		if(thead_)
		{
			return;
		}
		thead_ = new std::thread(&MyThread<T>::handle_function, this);
	}

	void Post(T* a)
	{
		std::lock_guard<std::mutex> lockguard_(mutex_);
		datas_.push_back(a);
	}

	void End_Join()
	{
		bLoop = false;
		if(thead_)
		{
			thead_->join();
		}
	}

	void Release()
	{
		if(thead_)
		{
			delete thead_;
			thead_ = nullptr;
		}
	}

	std::size_t task_count()
	{
		std::lock_guard<std::mutex> lockguard_(mutex_);
		return datas_.size();
	}

	void handle_function()
	{
		while(bLoop)
		{
			if(task_count()<=0)
			{
				continue;
			}

			std::lock_guard<std::mutex> lockguard_(mutex_);
			T* addr = datas_.front();
			T tmp = *addr;
			*addr = tmp+tmp;
			datas_.pop_front();
		}

		while(task_count()>0)
		{
			std::lock_guard<std::mutex> lockguard_(mutex_);
			T* addr = datas_.front();
			T tmp = *addr;
			*addr = tmp+tmp;
			datas_.pop_front();
		}
	}
protected:
	bool bLoop{true};
	std::thread* thead_{nullptr};

	std::deque<T*> datas_;
	std::mutex mutex_;
};

template<typename T>
class MyThreadPool
{
public:
	void Init(int thread_num)
	{
		thread_count_ = thread_num;
	}

	void Run()
	{
		if(arr_thread_)
		{
			return;
		}

		arr_thread_ = new MyThread<T>[thread_count_];
		for(int i=0; i<thread_count_; i++)
		{
			arr_thread_[i].Run();
		}
	}

	void Post(T* a)
	{
		int idle_id = find_idle_thread();
		if(idle_id==-1)
		{
			return;
		}
		arr_thread_[idle_id].Post(a);
	}

	void JoinExit()
	{
		if(arr_thread_)
		{
			for(int i=0; i<thread_count_; i++)
			{
				arr_thread_[i].End_Join();
			}
			delete []arr_thread_;
		}
	}

	int find_idle_thread()
	{
		int id = -1;
		int mintaskcount = std::numeric_limits<int>::max();
		for(int i=0; i<thread_count_; i++)
		{
			int num_val = arr_thread_[i].task_count();
			if(num_val==0)
			{
				id = i;
				break;
			}

			if(num_val<mintaskcount)
			{
				mintaskcount = num_val;
				id = i;
			}
		}
		return id;
	}
protected:
	MyThread<T> *arr_thread_{nullptr};
	int thread_count_{0};
};