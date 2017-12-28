#pragma once

#pragma warning(disable: 4819)

#include <iostream>
#include <atomic>
#include <deque>
#include <memory>
#include <mutex>

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

#include "boost.h"

#include "../dutil/define.h"

#include "packet.h"
#include "header.h"
#include "linear_buffer.h"
#include "basic_socket.h"
#include "basic_service.h"
#include "basic_acceptor.h"
#include "basic_connector.h"
#include "protocol/base_protocol.h"

#include "server.h"