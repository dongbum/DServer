#include "../define.h"

LogManager::LogManager(void)
	: today_(0)
	, log_mode_(LOG_MODE::LOG_MODE_NONE)
{

}


LogManager::~LogManager(void)
{
	if (log_mode_ & LOG_MODE::LOG_MODE_NONE)
		return;

	if (ofs_.is_open())
		ofs_.close();
}


bool LogManager::Init(void)
{
	today_ = GetTodayInt();

	log_mode_ = GetLogMode(CONFIG_MANAGER_INSTANCE.GetString("DServer", "LOG_MODE"));
	log_directory_name_ = CONFIG_MANAGER_INSTANCE.GetString("DServer", "LOG_PATH");
	log_file_name_ = CONFIG_MANAGER_INSTANCE.GetString("DServer", "LOG_FILE") + "_" + GetTodayStr() + ".log";

	if (log_mode_ & LOG_MODE::LOG_MODE_FILE)
	{
		if (false == CreateLogDirectory())
			return false;

		if (false == CreateLogFile())
			return false;
	}

	if ((log_mode_ & LOG_MODE::LOG_MODE_DISPLAY) || (log_mode_ & LOG_MODE::LOG_MODE_FILE))
		log_thread_ = boost::thread(boost::bind(&LogManager::Run, this));

	return true;
}


void LogManager::Write(LOG_LEVEL log_level, const char* format, ...)
{
	if (log_mode_ & LOG_MODE::LOG_MODE_NONE)
		return;

	LogMessage log_message;

	std::string date_str = "[" + GetTimeStr() + "] ";

	memcpy(log_message.GetBuffer(), date_str.c_str(), date_str.length());
	log_message.AddPosition(static_cast<unsigned int>(date_str.length()));

	va_list ap;
	va_start(ap, format);
	
	vsprintf_s(log_message.GetBuffer(), MAX_LOG_MESSAGE_LENGTH - log_message.GetPosition(), format, ap);

	va_end(ap);

	log_queue_.Push(log_message);
}


void LogManager::Run(void)
{
	while (true)
	{
		LogMessage log_message;

		log_message = log_queue_.Pop();

		if (log_mode_ & LOG_MODE::LOG_MODE_DISPLAY)
			std::cout << log_message.GetBufferStart() << std::endl;

		if (log_mode_ & LOG_MODE::LOG_MODE_FILE)
		{
			// 현재 날짜를 구하여 날짜가 지났는지 판단한다.
			if (today_ != GetTodayInt())
			{
				if (ofs_.is_open())
					ofs_.close();

				log_file_name_ = CONFIG_MANAGER_INSTANCE.GetString("DServer", "LOG_FILE") + "_" + GetTodayStr() + ".log";

				boost::filesystem::path path("./" + log_directory_name_);

				boost::filesystem::path file_path;
				if (true == FindFile(path, log_file_name_, file_path))
				{
					ofs_.open(file_path / log_file_name_, boost::filesystem::ofstream::out | boost::filesystem::ofstream::app);
				}
				else
				{
					ofs_.open(path / log_file_name_);
				}

				today_ = GetTodayInt();
			}

			ofs_ << std::string(log_message.GetBufferStart()) << '\n';
			ofs_.flush();
		}
	}
}


bool LogManager::CreateLogDirectory(void)
{
	try
	{
		boost::filesystem::path path("./" + log_directory_name_);

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


bool LogManager::CreateLogFile(void)
{
	try
	{
		boost::filesystem::path path("./" + log_directory_name_);

		boost::filesystem::path file_path;
		if (true == FindFile(path, log_file_name_, file_path))
		{
			ofs_.open(file_path / log_file_name_, boost::filesystem::ofstream::out | boost::filesystem::ofstream::app);
		}
		else
		{
			ofs_.open(path / log_file_name_);
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


bool LogManager::FindFile(const boost::filesystem::path& target_path, const std::string& file_name, OUT boost::filesystem::path& path)
{
	if (false == boost::filesystem::exists(target_path))
		return false;

	boost::filesystem::directory_iterator end_iter;
	for (boost::filesystem::directory_iterator iter(target_path); iter != end_iter; ++iter)
	{
		if (boost::filesystem::is_directory(iter->status()))
		{
			if (FindFile(iter->path(), file_name, path))
				return true;
		}
		else if (boost::filesystem::is_regular_file(iter->status()))
		{
			if (file_name == iter->path().leaf())
			{
				path = iter->path().parent_path();
				return true;
			}
		}
	}

	return false;
}


short LogManager::GetLogMode(const std::string& value)
{
	if (value == "NONE")
		return LOG_MODE::LOG_MODE_NONE;
	else if (value == "FILE")
		return LOG_MODE::LOG_MODE_FILE;
	else if (value == "DISPLAY")
		return LOG_MODE::LOG_MODE_DISPLAY;
	else if (value == "ALL")
		return (LOG_MODE::LOG_MODE_FILE | LOG_MODE::LOG_MODE_DISPLAY);
	else
		return (LOG_MODE::LOG_MODE_FILE | LOG_MODE::LOG_MODE_DISPLAY);
}
