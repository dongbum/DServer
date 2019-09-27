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

void Minidump::CreateCurrentProcessCrashDump(MINIDUMP_TYPE dump_type, TCHAR* filename, DWORD dwThread, EXCEPTION_POINTERS* exception_ptr)
{
	_ASSERT(false == IsBadReadPtr(exception_ptr, sizeof(EXCEPTION_POINTERS)));

	_ASSERT(0 != dwThread);

	HANDLE file = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	_ASSERT(INVALID_HANDLE_VALUE != file);

	if (INVALID_HANDLE_VALUE != file)
	{
		MINIDUMP_EXCEPTION_INFORMATION except_info;
		except_info.ThreadId = dwThread;
		except_info.ExceptionPointers = exception_ptr;
		except_info.ClientPointers = TRUE;
	}
}
#endif
