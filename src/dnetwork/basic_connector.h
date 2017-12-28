#pragma once

class BasicConnector
{
public:
	BasicConnector(IoService& io_service);
	virtual ~BasicConnector(void);

	bool Connect(std::string server_ip, const unsigned short server_port);
	void ConnectHandler(const ErrorCode& ec);

private:
	IoService& io_service_;
	BasicSocket socket_;
};

inline BasicConnector::BasicConnector(IoService& io_service)
	: io_service_(io_service)
	, socket_(io_service_)
{

}

inline BasicConnector::~BasicConnector(void)
{

}

inline bool BasicConnector::Connect(std::string server_ip, const unsigned short server_port)
{
	ErrorCode error_code;
	boost::asio::ip::address_v4 address = boost::asio::ip::address_v4::from_string(server_ip, error_code);
	if (error_code.value())
	{
		LL_DEBUG("Connect Failed. ErrorCode:[%d]", error_code.value());
		return false;
	}

	EndPoint end_point(address, server_port);

	Socket& socket = socket_.GetSocket();
	socket.async_connect(
		end_point,
		boost::bind(
			&BasicConnector::ConnectHandler,
			this,
			boost::asio::placeholders::error
		)
	);

	return true;
}

inline void BasicConnector::ConnectHandler(const ErrorCode& ec)
{
	LL_DEBUG("Connect. Remote Endpoint:[%s:%d]",
		socket_.GetSocket().remote_endpoint().address().to_string().c_str(),
		socket_.GetSocket().remote_endpoint().port());

	if (!ec)
	{
		socket_.OnReceive();
	}
}
