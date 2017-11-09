#include "define.h"

BasicSocket::BasicSocket(IoService& io_service)
	: socket_(io_service)
{
	memset(recv_buffer_, 0, RECV_BUFFER_SIZE);
	memset(send_buffer_, 0, RECV_BUFFER_SIZE);
}

BasicSocket::~BasicSocket(void)
{
	OnClose();
}

void BasicSocket::StartHandler(void)
{
}

void BasicSocket::OnReceive(void)
{
	memset(recv_buffer_, 0, RECV_BUFFER_SIZE);

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
	if (error)
	{
		if (boost::asio::error::eof)
		{
			// client closed.
		}

		OnClose();
		return;
	}


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

}

void BasicSocket::OnClose(void)
{
	if (!socket_.is_open())
		return;

	ErrorCode ignored_error;
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
	socket_.close();
}
