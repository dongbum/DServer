#include "define.h"

BasicSocket::BasicSocket(IoService& io_service)
	: socket_(io_service)
	, remain_size_(0)
	, strand_(io_service)
{
	memset(recv_buffer_, 0, RECV_BUFFER_SIZE);
	memset(send_buffer_, 0, SEND_BUFFER_SIZE);
	memset(packet_buffer_, 0, RECV_BUFFER_SIZE);
}

BasicSocket::~BasicSocket(void)
{
	OnClose();

	SendBufferPool::purge_memory();
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
		if (boost::asio::error::eof == error)
		{
			LL_DEBUG("Client connection end.");
		}
		else
		{
			LL_DEBUG("Client connection error:[%d] msg:[%s]", error.value(), error.message().c_str());
		}

		OnClose();
		return;
	}

	OnSend(bytes_transferred, recv_buffer_);
	OnReceive();
	return;

	// 패킷을 담아둘 버퍼에 수신버퍼의 내용을 복사한다.
	memcpy(&packet_buffer_[remain_size_], recv_buffer_, bytes_transferred);

	uint32_t packet_data_size = remain_size_ + static_cast<uint32_t>(bytes_transferred);
	uint32_t read_position = 0;

	while (packet_data_size > 0)
	{
		if (packet_data_size < sizeof(Header))
			break;

		Header* header = (Header*)&packet_buffer_[read_position];

		if (header->GetTotalLength() <= packet_data_size)
		{
			// 패킷 처리

			OnPacket(&packet_buffer_[read_position], header->GetTotalLength());

			packet_data_size -= header->GetTotalLength();
			read_position += header->GetTotalLength();
		}
		else
		{
			break;
		}
	}

	if (packet_data_size > 0)
	{
		if (packet_data_size > RECV_BUFFER_SIZE)
		{
			packet_data_size = RECV_BUFFER_SIZE;
		}

		// 남은 데이터가 있다면 패킷버퍼 맨 앞으로 이동한다.
		memmove(&packet_buffer_[0], &packet_buffer_[read_position], packet_data_size);
	}

	remain_size_ = packet_data_size;

	OnReceive();
}

void BasicSocket::OnSend(int size, char* data)
{
	ErrorCode error_code;
	EndPoint end_point = socket_.remote_endpoint(error_code);

	if (error_code)
	{
		LL_DEBUG("OnSend error:[%d] msg:[%s]", error_code.value(), error_code.message().c_str());
		OnClose();
		return;
	}

	char* send_data = static_cast<char*>(SendBufferPool::malloc());
	memcpy(send_data, data, size);

	boost::asio::async_write(socket_,
		boost::asio::buffer(send_data, size),
		strand_.wrap(
			[=](
				const ErrorCode& error,
				size_t bytes_transferred
				)
			{
				if (error)
				{
					LL_DEBUG("OnSendHandler error:[%d] msg:[%s]", error.value(), error.message().c_str());
					OnClose();
				}

				SendBufferPool::free(send_data);
			}
		)
	);
}

void BasicSocket::OnSendHandler(const ErrorCode& error, size_t bytes_transferred, char* send_data)
{
	if (error)
	{
		LL_DEBUG("OnSendHandler error:[%d] msg:[%s]", error.value(), error.message().c_str());
		OnClose();
	}

	SendBufferPool::free(send_data);
}

void BasicSocket::OnClose(void)
{
	if (true == socket_.is_open())
	{
		ErrorCode ignored_error;
		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
		socket_.close();
	}

	SendBufferPool::purge_memory();
}

void BasicSocket::OnPacket(char* packet, int size)
{
	LL_DEBUG("BasicSocket OnPacket");
}
