#pragma once

#include <iostream>
#include <atomic>

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

#define RECV_BUFFER_SIZE	1024
#define SEND_BUFFER_SIZE	1024

#include "boost.h"

#include "basic_socket.h"
#include "basic_service.h"
#include "basic_acceptor.h"
#include "server.h"