#pragma once

#include <cpp_redis/core/client.hpp>

class RedisConn
{
public:
	RedisConn(void);
	virtual ~RedisConn(void);

	bool	Connect(std::string& server_addr, std::string& server_port);
	bool	Disconnect(void);

protected:

private:
	boost::asio::io_context		io_service_;

	cpp_redis::client client_;

};
