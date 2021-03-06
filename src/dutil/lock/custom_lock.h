#pragma once

#ifdef _WIN32
#include <Windows.h>

class CustomLock
{
public:
	CustomLock(void)
	{
		if (false == InitializeCriticalSectionAndSpinCount(&cs, 4000))
		{
			LL_WARN("InitializeCriticalSectionAndSpinCount faild.");
				
		}
	}

	virtual ~CustomLock(void)
	{
		DeleteCriticalSection(&cs);
	}

	void lock(void)
	{
		EnterCriticalSection(&cs);
	}

	void unlock(void)
	{
		LeaveCriticalSection(&cs);
	}
private:
	CRITICAL_SECTION	cs;
};
#else
class CustomLock
{
public:
	CustomLock(void)
	{

	}

	virtual ~CustomLock(void)
	{

	}

	void lock(void)
	{
		mutex_.lock();
	}

	void unlock(void)
	{
		mutex_.unlock();
	}
private:
	std::mutex			mutex_;
};
#endif