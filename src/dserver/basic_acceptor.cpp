#include "define.h"

template<typename T>
BasicAcceptor<T>::BasicAcceptor(IoService& io_service, const unsigned short server_port)
	: io_service_(io_service)
	, acceptor_(io_service, EndPoint(TCP_V4, server_port))
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
	std::shared_ptr<Socket> socket_ptr(new Socket(io_service_));

	acceptor_.async_accept(
		*socket_ptr,
		boost::bind(
			&BasicAcceptor::AcceptHandler,
			this,
			socket_ptr,
			boost::asio::placeholders::error
		));

	return false;
}

template<typename T>
void BasicAcceptor<T>::AcceptHandler(std::shared_ptr<Socket> socket_ptr, const ErrorCode& ec)
{
	if (0 == ec)
	{
		(new T(socket_ptr))->StartHandler();
	}
	else
	{

	}

	if (is_stopped_)
		Init();
}

