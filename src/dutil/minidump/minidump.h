#pragma once

#include "../define.h"

#ifdef _WIN32
class Minidump
{
public:
	Minidump(void);
	virtual ~Minidump(void);

	bool Init(void);

private:
	static long WINAPI UnhandledExceptionFilter(EXCEPTION_POINTERS* exception_ptr);
	void CreateCurrentProcessCrashDump(MINIDUMP_TYPE dump_type, DWORD dwThread, EXCEPTION_POINTERS* exception_ptr);
};
#endif