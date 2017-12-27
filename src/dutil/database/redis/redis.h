#pragma once

class Redis
{
public:
	Redis(void);
	virtual ~Redis(void);

	bool	Connect(std::string& server_addr, std::string& server_port);
protected:

private:
	boost::asio::io_service		io_service_;
};
