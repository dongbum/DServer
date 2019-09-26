#pragma once

class LogManager
{
private:
	static std::shared_ptr<LogManager> instance_;

public:
	static std::shared_ptr<LogManager> GetInstance(void);
	static void ReleaseInstance(void);

public:
	LogManager(void);
	virtual ~LogManager(void);

	bool Init(void);
	void Write(LOG_LEVEL log_level, const char* format, ...);

private:
	void Run(void);

private:
	bool	CreateLogDirectory(void);
	bool	CreateLogFile(void);
	bool	FindFile(const boost::filesystem::path& target_path, const std::string& file_name, OUT boost::filesystem::path& path);
	short	GetLogMode(const std::string& value);

private:
	ThreadSafeQueue<LogMessage> log_queue_;
	boost::thread log_thread_;

	std::string		log_directory_name_;
	std::string		log_file_name_;
	short			log_mode_;

	std::ofstream	ofs_;

	unsigned int	today_;

};
