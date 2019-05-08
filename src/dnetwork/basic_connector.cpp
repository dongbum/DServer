#include "define.h"

BasicConnector::~BasicConnector(void)
{

}

bool BasicConnector::Connect(std::string server_ip, const unsigned short server_port)
{
	server_ip_ = server_ip;
	server_port_ = server_port;

	ErrorCode error_code;
	boost::asio::ip::address_v4 address = boost::asio::ip::make_address_v4(server_ip, error_code);
	if (error_code.value())
	{
		LL_DEBUG("Connect Failed. ErrorCode:[%d]", error_code.value());
		return false;
	}

	EndPoint end_point(address, server_port);

	Socket& socket = GetSocket();
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

void BasicConnector::ConnectHandler(const ErrorCode& error)
{
	if (error)
	{
		if (boost::asio::error::eof == error)
		{
			LL_DEBUG("Client connection end.");
		}
		else
		{
			LL_DEBUG("Client connection error:[%d] msg:[%s]", error.value(), error.message().c_str());
		}

		BaseClass::OnClose();
		ReConnect();
		return;
	}

	Socket& socket = GetSocket();

	LL_DEBUG("Connect. Remote Endpoint:[%s:%d]",
		socket.remote_endpoint().address().to_string().c_str(),
		socket.remote_endpoint().port());

	OnReceive();
}

void BasicConnector::ReConnect(void)
{
	Connect(server_ip_, server_port_);
}
