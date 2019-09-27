#pragma once

#include "../define.h"

#ifdef _WIN32
typedef enum tag_BSUMDRET
{
	eDUMP_SUCCEEDED = 0,		// Everything worked.
	eDBGHELP_NOT_FOUND,			// DBGHELP.DLL could not be found at all in the path.
	eDBGHELP_MISSING_EXPORTS,	// The mini dump exports are not in the version of DBGHELP.DLL in memory.
	eBAD_PARAM,					// A parameter was bad.
	eOPEN_DUMP_FAILED,			// Unable to open the dump file requested.
	eMINIDUMPWRITEDUMP_FAILED,	// MiniDumpWriteDump failed.  Call GetLastError to see why.
	eGETTHREADCONTEXT_FAILED,	// Unable to get the thread context.
	eREADPROCMEM_FAILED,		// Unable to read the process memory.
	eINVALID_ERROR,				// The invalid error value.
} BSUMDRET;

class Minidump
{
private:
	static std::shared_ptr<Minidump> instance_;

public:
	static std::shared_ptr<Minidump> GetInstance(void);
	static void ReleaseInstance(void);

public:
	Minidump(void);
	virtual ~Minidump(void);

	bool Init(std::string pAppPath, std::string pFileName);
	static bool CreateMinidumpDirectory(std::string directory_path);

private:
	typedef BOOL(WINAPI *PFNMINIDUMPWRITEDUMP)(
		IN HANDLE hProcess, IN DWORD ProcessId, IN HANDLE hFile, IN MINIDUMP_TYPE DumpType,
		IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
		OPTIONAL IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
		OPTIONAL IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL);

	static long WINAPI UnhandledExceptionFilter(EXCEPTION_POINTERS* exception_ptr);
	bool __stdcall	isMiniDumpFunctionAvailable(void);
	BSUMDRET __stdcall CreateCurrentProcessCrashDump(MINIDUMP_TYPE dump_type, TCHAR* filename, DWORD dwThread, EXCEPTION_POINTERS* exception_ptr);

private:
	PFNMINIDUMPWRITEDUMP pfn_write_dump;
	BSUMDRET last_error;

	static std::string app_path;
	static std::string minidump_filename;
};
#endif