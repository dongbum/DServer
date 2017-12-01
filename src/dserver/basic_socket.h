#pragma once


class BasicSocket : public std::enable_shared_from_this<BasicSocket>
{
public:
	struct SEND_BUFFER_TAG {};
	typedef boost::singleton_pool<SEND_BUFFER_TAG, SEND_BUFFER_SIZE> SendBufferPool;

	BasicSocket(IoService& io_service);
	virtual ~BasicSocket(void);

	void OnReceive(void);
	void OnReceiveHandler(const ErrorCode& error, size_t bytes_transferred);

	void OnSend(int size, char* data);
	void OnSendHandler(const ErrorCode& error, size_t bytes_transferred, char* send_data);

	virtual void OnClose(void);

	virtual void OnPacket(char* packet, int size);

	Socket& GetSocket(void) { return socket_; };
	
protected:
	std::shared_ptr<Socket> socket_ptr_;

	Socket socket_;

	char packet_buffer_[RECV_BUFFER_SIZE * 2];
	int32_t remain_size_;

	char recv_buffer_[RECV_BUFFER_SIZE];
	char send_buffer_[SEND_BUFFER_SIZE];

	Strand strand_;
};
