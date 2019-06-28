#pragma once

#include <mutex>

template<std::size_t ObjSize, std::size_t PoolSize = 10>
class MyAllocator
{
protected:
	struct ObjAllocator
	{
		char data[ObjSize];
		ObjAllocator* next;
	};
	struct ChunkAllocator
	{
		ObjAllocator data[PoolSize];
		ChunkAllocator* next;
	};
	ObjAllocator* obj_available_head{nullptr};
	ChunkAllocator* chunk_allocated_head{nullptr};
public:
	MyAllocator(){}
	~MyAllocator()
	{
		ChunkAllocator* p;
		while(chunk_allocated_head)
		{
			p = chunk_allocated_head->next;
			delete chunk_allocated_head;chunk_allocated_head=nullptr;
			chunk_allocated_head = p;
		}
	}
	void* allocate()
	{
		if(obj_available_head==nullptr)
		{
			ChunkAllocator* chunk_new = new ChunkAllocator();
			chunk_new->next = nullptr;
			for(int i=1; i<PoolSize; i++)
			{
				chunk_new->data[i-1].next = &(chunk_new->data[i]);
			}
			chunk_new->data[PoolSize-1].next = nullptr;
			obj_available_head = &(chunk_new->data[0]);

			if(chunk_allocated_head)
			{
				chunk_new->next = chunk_allocated_head;
				chunk_allocated_head = chunk_new;
			}
			else
			{
				chunk_allocated_head = chunk_new;
			}
		}

		void* obj_return = obj_available_head;
		obj_available_head = obj_available_head->next;
		return obj_return;
	}
	void disallocate(void* p)
	{
		ObjAllocator* obj_release = (ObjAllocator*)p;
		obj_release->next = obj_available_head;
		obj_available_head = obj_release;
	}
};

template<typename T, std::size_t PoolSize = 10>
class MyMemoPool:public MyAllocator<sizeof(T), PoolSize>
{
public:
	template<typename ...Args>
	T* my_construct(Args ...args)
	{
		mutex_.lock();
		void* p = this->allocate();
		mutex_.unlock();

		if(p==nullptr)
		{
			return nullptr;
		}
		else
		{
			T* pt = new (p)T(args...);
			return pt;
		}
	}
	void my_disconstruct(T* obj)
	{
		obj->~T();
		mutex_.lock();
		this->disallocate(obj);
		mutex_.unlock();
	}
protected:
	std::mutex mutex_;
};