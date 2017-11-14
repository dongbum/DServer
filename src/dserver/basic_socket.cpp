#include "define.h"

BasicSocket::BasicSocket(IoService& io_service)
	: socket_(io_service)
{
	memset(recv_buffer_, 0, RECV_BUFFER_SIZE);
	memset(send_buffer_, 0, SEND_BUFFER_SIZE);
}

BasicSocket::~BasicSocket(void)
{
	OnClose();
}

void BasicSocket::OnReceive(void)
{
	socket_.async_read_some(
		boost::asio::buffer(recv_buffer_),
		boost::bind(
			&BasicSocket::OnReceiveHandler,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void BasicSocket::OnReceiveHandler(const ErrorCode& error, size_t bytes_transferred)
{
	std::cout << "OnReceive bytes_transferred:" << bytes_transferred << std::endl;

	if (error || bytes_transferred < sizeof(Header))
	{
		if (boost::asio::error::eof)
		{
			std::cout << "Client connection end." << std::endl;
		}

		OnClose();
		return;
	}

	OnPacket(recv_buffer_, bytes_transferred);

	OnReceive();
}

void BasicSocket::OnSend(int size, char* data)
{
	ErrorCode error_code;
	EndPoint end_point = socket_.remote_endpoint(error_code);

	if (error_code)
	{
		OnClose();
		return;
	}

	char send_data[SEND_BUFFER_SIZE] = { 0, };
	int send_data_size = 0;

	memcpy(send_data, data, size);
	send_data_size = size;

	boost::asio::async_write(socket_,
		boost::asio::buffer(send_data, send_data_size),
		boost::bind(
			&BasicSocket::OnSendHandler,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void BasicSocket::OnSendHandler(const ErrorCode& error, size_t bytes_transferred)
{
	std::cout << "OnSendHandler" << std::endl;
}

void BasicSocket::OnClose(void)
{
	if (!socket_.is_open())
		return;

	ErrorCode ignored_error;
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
	socket_.close();
}

void BasicSocket::OnPacket(char* packet, int size)
{
	std::cout << "BasicSocket OnPacket" << std::endl;
}
