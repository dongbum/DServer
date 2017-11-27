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


template<typename T>
BasicAcceptor<T>::BasicAcceptor(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool, const unsigned short server_port)
	: io_service_(io_service)
	, acceptor_(io_service_, EndPoint(TCP_V4, server_port))
	, session_pool_(session_pool)
	, is_stopped_(false)
{

}

template<typename T>
BasicAcceptor<T>::~BasicAcceptor(void)
{

}

template<typename T>
void BasicAcceptor<T>::Start(void)
{
	acceptor_.listen();
	Init();
}

template<typename T>
void BasicAcceptor<T>::Stop(void)
{
	is_stopped_.store(true);
}

template<typename T>
bool BasicAcceptor<T>::Init(void)
{
	std::shared_ptr<T> new_session = nullptr;
	new_session = session_pool_.GetPoolObject();

	acceptor_.async_accept(
		new_session->GetSocket(),
		boost::bind(
			&BasicAcceptor<T>::AcceptHandler,
			this,
			new_session,
			boost::asio::placeholders::error
		)
	);

	return true;
}

template<typename T>
void BasicAcceptor<T>::AcceptHandler(std::shared_ptr<T> socket_ptr, const ErrorCode& ec)
{
	std::cout << "Accept" << std::endl;
	if (0 == ec)
	{
		try
		{
			socket_ptr->OnReceive();
		}
		catch (...)
		{

		}
	}
	else
	{

	}

	if (false == is_stopped_.load())
		Init();
	else
		acceptor_.close();
}

