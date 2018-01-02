#pragma once

template<typename T>
class BasicAcceptor
{
public:
	BasicAcceptor(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool, const unsigned short server_port);
	virtual ~BasicAcceptor(void);

	void Start(void);
	void Stop(void);

private:
	bool Init(void);
	void AcceptHandler(std::shared_ptr<T> socket_ptr, const ErrorCode& ec);

private:
	IoService& io_service_;
	Acceptor acceptor_;
	ObjectPool<std::shared_ptr<BasicSocket>>& session_pool_;

	std::atomic<bool> is_stopped_;

};
