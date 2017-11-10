#pragma once

template<typename T>
class BasicAcceptor
{
public:
	BasicAcceptor(IoService& io_service, const unsigned short server_port);
	virtual ~BasicAcceptor(void);

	void Start(void);
	void Stop(void);

private:
	bool Init(void);
	void AcceptHandler(std::shared_ptr<T> socket_ptr, const ErrorCode& ec);

private:
	IoService& io_service_;
	Acceptor acceptor_;

	std::atomic<bool> is_stopped_;

};


template<typename T>
BasicAcceptor<T>::BasicAcceptor(IoService& io_service, const unsigned short server_port)
	: io_service_(io_service)
	, acceptor_(io_service_, EndPoint(TCP_V4, server_port))
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
	std::shared_ptr<T> socket_ptr(new T(io_service_));

	acceptor_.async_accept(
		socket_ptr->GetSocket(),
		boost::bind(
			&BasicAcceptor<T>::AcceptHandler,
			this,
			socket_ptr,
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

