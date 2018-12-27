#pragma once

class MemoryPool
{
public:
	MemoryPool(void) {}
	virtual ~MemoryPool(void) {}

#ifdef _WIN32
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
#endif

private:
};
