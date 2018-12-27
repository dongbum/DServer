#pragma once

template<typename T>
class ObjectPool
{
public:
	ObjectPool(void) {};
	virtual ~ObjectPool(void) {};

	void PushObject(T& object_ptr)
	{
		object_queue_.Push(object_ptr);
	}

	T GetPoolObject(void)
	{
		T object_ptr = object_queue_.Pop();
		return object_ptr;
	}

	void ReleasePoolObject(T object_ptr)
	{
		object_queue_.Push(object_ptr);
	}

	size_t Size(void)
	{
		return object_queue_.Size();
	}

private:
	ThreadSafeQueue<T>	object_queue_;

};