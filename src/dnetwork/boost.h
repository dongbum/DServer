#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/serialization/singleton.hpp>

#include <boost/pool/singleton_pool.hpp>
#include <boost/pool/pool_alloc.hpp>

#define TCP_V4	boost::asio::ip::address_v4::any()
#define TCP_V6	boost::asio::ip::address_v6::any()

using Strand = boost::asio::strand;
using IoService = boost::asio::io_service;
using Work = boost::asio::io_service::work;
using EndPoint = boost::asio::ip::tcp::endpoint;
using Acceptor = boost::asio::ip::tcp::acceptor;
using Socket = boost::asio::ip::tcp::socket;
using ErrorCode = boost::system::error_code;

using Mutex = boost::mutex;
using LockGuard = boost::lock_guard<Mutex>;