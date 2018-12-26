#ifdef _WIN32

#pragma once

class MemoryPool
{
public:
	MemoryPool(void) {}
	virtual ~MemoryPool(void) {}

	void* operator new(size_t size)
	{
		return je_malloc(size);
	}

	void* operator new[](size_t size)
	{
		return je_malloc(size);
	}

	void operator delete(void* ptr)
	{
		je_free(ptr);
	}

	void operator delete[](void* ptr)
	{
		je_free(ptr);
	}
private:
};

#endif