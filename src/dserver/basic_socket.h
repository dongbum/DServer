#pragma once


class BasicSocket : public std::enable_shared_from_this<BasicSocket>
{
public:
	BasicSocket(IoService& io_service);
	virtual ~BasicSocket(void);

	void StartHandler(void);

	void OnReceive(void);
	void OnReceiveHandler(const ErrorCode& error, size_t bytes_transferred);

	void OnSend(int size, char* data);
	void OnSendHandler(const ErrorCode& error, size_t bytes_transferred);

	void OnClose(void);

	virtual void OnPacket(void);

	Socket& GetSocket(void) { return socket_; };

protected:
	std::shared_ptr<Socket> socket_ptr_;

private:
	Socket socket_;

	char recv_buffer_[RECV_BUFFER_SIZE];
	char send_buffer_[SEND_BUFFER_SIZE];
};
