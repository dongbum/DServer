#include "minidump.h"

#ifdef _WIN32
Minidump::Minidump(void)
{
}

Minidump::~Minidump(void)
{
}

bool Minidump::Init(void)
{
	SetUnhandledExceptionFilter(UnhandledExceptionFilter);

	return true;
}

long WINAPI Minidump::UnhandledExceptionFilter(EXCEPTION_POINTERS* exception_ptr)
{
	return 0;
}

void Minidump::CreateCurrentProcessCrashDump(MINIDUMP_TYPE dump_type, DWORD dwThread, EXCEPTION_POINTERS* exception_ptr)
{
	_ASSERT(false == IsBadReadPtr(exception_ptr, sizeof(EXCEPTION_POINTERS)));

	_ASSERT(0 != dwThread);
}
#endif
