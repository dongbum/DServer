#pragma once

#pragma warning(disable: 4819)

#include <iostream>
#include <atomic>
#include <deque>
#include <memory>
#include <mutex>

#ifdef _WIN64
#	ifdef _DEBUG
#		define LIB_NAME(LIB) LIB##"64D.lib"
#	else
#		define LIB_NAME(LIB) LIB##"64.lib"
#	endif
#else
#	ifdef _DEBUG
#		define LIB_NAME(LIB) LIB##"D.lib"
#	else
#		define LIB_NAME(LIB) LIB##".lib"
#	endif
#endif	// x64

#pragma comment(lib, LIB_NAME("jemalloc"))
#pragma comment(lib, LIB_NAME("lib_json"))

#ifndef _WIN32_WINNT         
#define _WIN32_WINNT	0x0501
#endif

#ifndef CPPCONN_LIB_BUILD
#define CPPCONN_LIB_BUILD True
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")
#endif

#define RECV_BUFFER_SIZE			1024
#define SEND_BUFFER_SIZE			1024
#define MAX_LOG_MESSAGE_LENGTH		1024
#define MAX_DATETIME_SIZE			(19+1)

#define SAFE_DELETE(p)				{ if ( p ) delete p; p = nullptr; } 
#define SAFE_DELETE_ARRAY(p)		{ if ( p ) delete[] p; p = nullptr; }

#include <jemalloc/jemalloc.h>
#include <json/json.h>

#include "boost.h"
#include "memorypool/memory_pool.h"
#include "database.h"

#include "container/thread_safe_queue.h"
#include "utility/util.h"
#include "config/config.h"
#include "logging/log_define.h"
#include "logging/log_message.h"
#include "logging/log_manager.h"
#include "lock/custom_lock.h"
#include "database/mysql/mysql_conn.h"
#include "database/mysql/mysql_conn_pool.h"
#include "database/mssql/mssql_define.h"
#include "database/mssql/mssql_conn.h"
#include "database/mssql/mssql_conn_pool.h"
#include "database/redis/redis.h"
#include "monitor/system_resource_monitor.h"
#include "object_pool.h"
