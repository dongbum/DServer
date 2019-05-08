#pragma once

class BasicConnector : public BasicSocket
{
public:
	using BaseClass = BasicSocket;

	explicit BasicConnector(IoContext& io_context);
	virtual ~BasicConnector(void);

	bool Connect(std::string server_ip, const unsigned short server_port);
	void ConnectHandler(const ErrorCode& ec);
	void ReConnect(void);

private:
	std::string server_ip_;
	unsigned short server_port_;
};

inline BasicConnector::BasicConnector(IoContext& io_context)
	: BasicSocket(io_context)
	, server_ip_("127.0.0.1")
	, server_port_(0)
{

}
