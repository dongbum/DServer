#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <boost/pool/singleton_pool.hpp>
#include <boost/pool/pool_alloc.hpp>

#define TCP_V4	boost::asio::ip::address_v4::any()
#define TCP_V6	boost::asio::ip::address_v6::any()

typedef boost::asio::strand				Strand;
typedef boost::asio::io_service			IoService;
typedef boost::asio::io_service::work	Work;
typedef boost::asio::ip::tcp::endpoint	EndPoint;
typedef boost::asio::ip::tcp::acceptor	Acceptor;
typedef boost::asio::ip::tcp::socket	Socket;
typedef boost::system::error_code		ErrorCode;

typedef boost::mutex					Mutex;
typedef boost::lock_guard<Mutex>		LockGuard;