#include "../../define.h"

RedisConn::RedisConn(void)
{

}
	
RedisConn::~RedisConn(void)
{
	if (true == client_.is_connected())
		client_.disconnect();

}

bool RedisConn::Connect(std::string& server_addr, std::string& server_port)
{
	if (true == client_.is_connected())
		client_.disconnect();

	client_.connect(server_addr, stoi(server_port), [](const std::string& host, std::size_t port, cpp_redis::connect_state status)
	{
		switch (status)
		{
		case cpp_redis::connect_state::ok:
			LL_DEBUG("REDIS Connect SUCCESS");
			break;
		case cpp_redis::connect_state::start:
			LL_DEBUG("REDIS Connect START");
			break;
		case cpp_redis::connect_state::dropped:
		case cpp_redis::connect_state::sleeping:
		case cpp_redis::connect_state::failed:
		case cpp_redis::connect_state::lookup_failed:
		case cpp_redis::connect_state::stopped:
		default:
			LL_DEBUG("REDIS Connect FAILED");
			break;
		}
	});

	return true;
}

bool RedisConn::Disconnect(void)
{
	if (true == client_.is_connected())
		client_.disconnect();

	return true;
}
