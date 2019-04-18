#pragma once

#include <cpp_redis/core/client.hpp>

class Redis
{
public:
	Redis(void);
	virtual ~Redis(void);

	bool	Connect(std::string& server_addr, std::string& server_port);

protected:

private:
	boost::asio::io_service		io_service_;

	cpp_redis::client client_;

};
