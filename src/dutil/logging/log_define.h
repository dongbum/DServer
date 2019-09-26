#pragma once

#define MAX_LOG_MESSAGE_LENGTH		1024

#define LL_DEBUG(...)		LogManager::GetInstance()->Write(LOG_LEVEL_DEBUG, __VA_ARGS__);
#define LL_INFO(...)		LogManager::GetInstance()->Write(LOG_LEVEL_INFO, __VA_ARGS__);
#define LL_WARN(...)		LogManager::GetInstance()->Write(LOG_LEVEL_WARN, __VA_ARGS__);
#define LL_ERROR(...)		LogManager::GetInstance()->Write(LOG_LEVEL_ERROR, __VA_ARGS__);
#define LL_FATAL(...)		LogManager::GetInstance()->Write(LOG_LEVEL_FATAL, __VA_ARGS__);


enum LOG_LEVEL : short
{
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_FATAL,
	LOG_LEVEL_MAX
};

enum LOG_MODE : short
{
	LOG_MODE_NONE =			0x00000001,
	LOG_MODE_FILE =			0x00000010,
	LOG_MODE_DISPLAY =		0x00000100,
	LOG_MODE_MAX =			0x00001000,
};
