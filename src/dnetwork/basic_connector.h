#pragma once

class BasicConnector : public BasicSocket
{
public:
	BasicConnector(IoService& io_service);
	virtual ~BasicConnector(void);

	bool Connect(std::string server_ip, const unsigned short server_port);
	void ConnectHandler(const ErrorCode& ec);
	void ReConnect(void);

private:
	std::string server_ip_;
	unsigned short server_port_;
};

inline BasicConnector::BasicConnector(IoService& io_service)
	: BasicSocket(io_service)
	, server_ip_("127.0.0.1")
	, server_port_(0)
{

}
