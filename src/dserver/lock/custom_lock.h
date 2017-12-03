#pragma once

class CustomLock
{
public:
	CustomLock(void)
	{
		InitializeCriticalSection(&cs);
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
	std::mutex			mutex_;
};