#pragma once

template<typename T>
class BasicAcceptor
{
public:
	BasicAcceptor(IoContext& io_context, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool, const unsigned short server_port);
	virtual ~BasicAcceptor(void);

	void Start(void);
	void Stop(void);

private:
	bool Init(void);
	void AcceptHandler(std::shared_ptr<T> socket_ptr, const ErrorCode& ec);

private:
	IoContext& io_context_;
	Acceptor acceptor_;
	ObjectPool<std::shared_ptr<BasicSocket>>& session_pool_;

	std::atomic<bool> is_stopped_;

};

template<typename T>
BasicAcceptor<T>::BasicAcceptor(IoContext& io_context, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool, const unsigned short server_port)
	: io_context_(io_context)
	, acceptor_(io_context_, EndPoint(TCP_V4, server_port))
	, session_pool_(session_pool)
	, is_stopped_(false)
{
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
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
	LL_DEBUG("Accept. Remote Endpoint:[%s:%d]",
		std::static_pointer_cast<BasicSocket>(socket_ptr)->GetSocket().remote_endpoint().address().to_string().c_str(),
		std::static_pointer_cast<BasicSocket>(socket_ptr)->GetSocket().remote_endpoint().port());

	if (false == acceptor_.is_open())
	{
		return;
	}

	if (!ec)
	{
		try
		{
			socket_ptr->OnReceive();
		}
		catch (...)
		{
			socket_ptr->OnClose();
		}
	}
	else
	{
		socket_ptr->OnClose();
	}

	if (false == is_stopped_.load())
		Init();
	else
		acceptor_.close();
}
