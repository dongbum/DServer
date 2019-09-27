#pragma once

#include "../define.h"

#ifdef _WIN32
class Minidump
{
public:
	Minidump(void);
	virtual ~Minidump(void);

	static void SetHandlerDump(void);
	static bool Init(std::string minidump_path, std::string minidump_filename);
	static bool CreateMinidumpDirectory(std::string directory_path);

private:
	static long WINAPI UnhandledExceptionFilter(EXCEPTION_POINTERS* exception_ptr);
	static void myInvaildParameterHandler(const wchar_t* expression, const wchar_t* function, const wchar_t* file, unsigned int lien, uintptr_t pReserverd);
	static void _custom_Report_hook(int ireposttype, char *message, int *returnvalue);
	static void myPurecallHandler(void);

private:
	static std::string app_path_;
	static std::string minidump_filename_;

	static LPTOP_LEVEL_EXCEPTION_FILTER PreviousExceptionFilter;
};
#endif