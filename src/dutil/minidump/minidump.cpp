#include "minidump.h"

#ifdef _WIN32

const TCHAR* const DBGHelpDllName = _T("DBGHELP.DLL");
std::string Minidump::app_path = "";
std::string Minidump::minidump_filename = "";

std::shared_ptr<Minidump> Minidump::instance_ = nullptr;

std::shared_ptr<Minidump> Minidump::GetInstance(void)
{
	if (nullptr == instance_)
		instance_ = std::shared_ptr<Minidump>(new Minidump());

	return instance_;
}

void Minidump::ReleaseInstance(void)
{
	instance_.reset();
}

Minidump::Minidump(void)
	: pfn_write_dump(NULL)
	, last_error(eINVALID_ERROR)
{
}

Minidump::~Minidump(void)
{
}

bool Minidump::Init(std::string pAppPath, std::string pFileName)
{
	app_path = pAppPath;
	minidump_filename = pFileName;

	SetUnhandledExceptionFilter(UnhandledExceptionFilter);

	return true;
}

bool Minidump::CreateMinidumpDirectory(std::string directory_path)
{
	try
	{
		boost::filesystem::path path(directory_path);

		if (false == boost::filesystem::exists(path))
		{
			if (false == boost::filesystem::create_directory(path))
			{
				std::cout << "CreateDirectory failed." << std::endl;
				return false;
			}
		}
	}
	catch (boost::filesystem::filesystem_error& fe)
	{
		std::cout << fe.code() << " - " << fe.what() << std::endl;
		return false;
	}
	catch (ErrorCode& ec)
	{
		std::cout << ec.value() << " - " << ec.message() << std::endl;
		return false;
	}

	return true;
}

long WINAPI Minidump::UnhandledExceptionFilter(EXCEPTION_POINTERS* exception_ptr)
{
	time_t curr_time = time(NULL);
	struct tm* curr_tm = gmtime(&curr_time);
	curr_tm->tm_hour = (curr_tm->tm_hour + UTC_SEOUL) % 24;

	char buffer[1024] = "";
	strftime(buffer, sizeof(buffer), "[%Y-%m-%d][%H:%M:%S]", curr_tm);

	std::string full_path = "";
	full_path += app_path;
	full_path += "\\MiniDump_" + minidump_filename + "_";
	full_path += std::string(buffer);
	full_path += ".dmp";

	if (false == CreateMinidumpDirectory(app_path))
		return EXCEPTION_EXECUTE_HANDLER;

	CA2T full_path_t(full_path.c_str());
	BSUMDRET eCCPMD = Minidump::GetInstance()->CreateCurrentProcessCrashDump(
		(MINIDUMP_TYPE)(MiniDumpWithFullMemory),
		full_path_t, GetCurrentThreadId(), exception_ptr);

	_ASSERT(eDUMP_SUCCEEDED == eCCPMD);

	return EXCEPTION_EXECUTE_HANDLER;
}

bool __stdcall Minidump::isMiniDumpFunctionAvailable(void)
{
	if (NULL != pfn_write_dump)
	{
		HINSTANCE hInstDBGHELP = GetModuleHandle(DBGHelpDllName);
		if (NULL == hInstDBGHELP)
			hInstDBGHELP = LoadLibrary(DBGHelpDllName);

		if (NULL == hInstDBGHELP)
		{
			last_error = eDBGHELP_NOT_FOUND;
			return false;
		}

		pfn_write_dump = (PFNMINIDUMPWRITEDUMP)GetProcAddress(hInstDBGHELP, "MiniDumpWriteDump");

		if (NULL != pfn_write_dump)
			last_error = eDUMP_SUCCEEDED;
		else
			last_error = eDBGHELP_MISSING_EXPORTS;
	}

	return (NULL != pfn_write_dump);
}

BSUMDRET __stdcall Minidump::CreateCurrentProcessCrashDump(MINIDUMP_TYPE dump_type, TCHAR* filename, DWORD dwThread, EXCEPTION_POINTERS* exception_ptr)
{
	BSUMDRET result = eOPEN_DUMP_FAILED;

	_ASSERT(false == IsBadStringPtr(filename, MAX_PATH));
	if (true == IsBadStringPtr(filename, MAX_PATH))
		return eBAD_PARAM;

	_ASSERT(false == IsBadReadPtr(exception_ptr, sizeof(EXCEPTION_POINTERS)));
	if (true == IsBadReadPtr(exception_ptr, sizeof(EXCEPTION_POINTERS)))
		return eBAD_PARAM;

	_ASSERT(0 != dwThread);
	if (0 == dwThread)
		return eBAD_PARAM;

	if ((NULL == pfn_write_dump) && (eINVALID_ERROR == last_error))
	{
		if (FALSE == isMiniDumpFunctionAvailable())
			return last_error;
	}

	if (NULL == pfn_write_dump)
		return last_error;

	HANDLE file_handle = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	_ASSERT(INVALID_HANDLE_VALUE != file_handle);

	if (INVALID_HANDLE_VALUE != file_handle)
	{
		MINIDUMP_EXCEPTION_INFORMATION except_info;
		except_info.ThreadId = dwThread;
		except_info.ExceptionPointers = exception_ptr;
		except_info.ClientPointers = TRUE;

		BOOL dump_result = pfn_write_dump(GetCurrentProcess(), GetCurrentProcessId(), file_handle, dump_type, &except_info, NULL, NULL);
		_ASSERT(TRUE == dump_result);

		if (TRUE == dump_result)
			last_error = eDUMP_SUCCEEDED;
		else
			last_error = eMINIDUMPWRITEDUMP_FAILED;

		CloseHandle(file_handle);
	}
	else
	{
		last_error = eOPEN_DUMP_FAILED;
	}

	return last_error;
}
#endif
