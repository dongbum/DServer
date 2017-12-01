#pragma once

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
#endif

#define RECV_BUFFER_SIZE	1024
#define SEND_BUFFER_SIZE	1024

#include "boost.h"

#include "container/thread_safe_queue.h"
#include "object_pool.h"
#include "header.h"
#include "linear_buffer.h"
#include "basic_socket.h"
#include "basic_service.h"
#include "basic_acceptor.h"
#include "protocol/base_protocol.h"
#include "server.h"