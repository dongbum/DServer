#pragma once

class TCWrapper
{
public:
	TCWrapper(void) {}
	virtual ~TCWrapper(void) {}

	void* operator new(size_t size)
	{
		return tc_new(size);
	}

	void* operator new[](size_t size)
	{
		return tc_new(size);
	}

	void operator delete(void* ptr)
	{
		tc_delete(ptr);
	}

	void operator delete[](void* ptr)
	{
		tc_delete(ptr);
	}
};
