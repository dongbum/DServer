#include "minidump.h"

#ifdef _WIN32

std::string Minidump::app_path_ = "";
std::string Minidump::minidump_filename_ = "";
LPTOP_LEVEL_EXCEPTION_FILTER Minidump::PreviousExceptionFilter;

Minidump::Minidump(void)
{
	PreviousExceptionFilter = nullptr;

	_invalid_parameter_handler oldHandler, newHandler;
	newHandler = myInvaildParameterHandler;

	// CRT가 잘못된 인수를 발견할 때 호출할 함수를 설정
	// return : A pointer to the invalid parameter handler before the call
	oldHandler = _set_invalid_parameter_handler(newHandler);

	// CRT 오류 메시지 표시 중단하고 바로 덤프로 남도록 함
	_CrtSetReportMode(_CRT_WARN, 0);
	_CrtSetReportMode(_CRT_ASSERT, 0);
	_CrtSetReportMode(_CRT_ERROR, 0);

	// 순수 가상 함수 호출에 대한 오류 처리
	// pure virtual function called 에러 핸들러를 사용자 정의 함수로 우회
	_set_purecall_handler(myPurecallHandler);

	SetHandlerDump();
}

Minidump::~Minidump(void)
{
	SetUnhandledExceptionFilter(PreviousExceptionFilter);
}

void Minidump::SetHandlerDump(void)
{
	PreviousExceptionFilter = SetUnhandledExceptionFilter(UnhandledExceptionFilter);
}

bool Minidump::Init(std::string minidump_path, std::string minidump_filename)
{
	app_path_ = minidump_path;
	minidump_filename_ = minidump_filename;

	PreviousExceptionFilter = SetUnhandledExceptionFilter(UnhandledExceptionFilter);

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

long Minidump::UnhandledExceptionFilter(EXCEPTION_POINTERS* exception_ptr)
{
	time_t curr_time = time(NULL);
	struct tm curr_tm;
	gmtime_s(&curr_tm, &curr_time);
	curr_tm.tm_hour = (curr_tm.tm_hour + UTC_SEOUL) % 24;

	char buffer[1024] = "";
	strftime(buffer, sizeof(buffer), "[%Y-%m-%d][%H%M%S]", &curr_tm);

	std::string full_path = "";
	full_path += app_path_;
	full_path += "MiniDump_" + minidump_filename_ + "_";
	full_path += std::string(buffer);
	full_path += ".dmp";

	std::cout << full_path.c_str() << std::endl;

	if (false == CreateMinidumpDirectory(app_path_))
		return EXCEPTION_EXECUTE_HANDLER;

	USES_CONVERSION;
	std::wstring full_path_t(A2W(full_path.c_str()));

	wprintf(L"full_path_t : %s", full_path_t.c_str());
	HANDLE file_handle = CreateFile(full_path_t.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE != file_handle)
	{
		std::cout << "111 START" << std::endl;
		MINIDUMP_EXCEPTION_INFORMATION except_info;
		except_info.ThreadId = GetCurrentThreadId();
		except_info.ExceptionPointers = exception_ptr;
		except_info.ClientPointers = TRUE;

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file_handle, MiniDumpWithFullMemory, &except_info, nullptr, nullptr);

		CloseHandle(file_handle);
	}
	else
	{
		std::cout << "111 - 1111 START" << std::endl;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

void Minidump::myInvaildParameterHandler(const wchar_t * expression, const wchar_t * function, const wchar_t * file, unsigned int lien, uintptr_t pReserverd)
{
	CRASH
}

void Minidump::_custom_Report_hook(int ireposttype, char * message, int * returnvalue)
{
	CRASH
}

void Minidump::myPurecallHandler(void)
{
	CRASH
}

#endif
