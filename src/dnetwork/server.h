#pragma once

template<typename T>
class Server : public MemoryPool
{
public:
	Server(int32_t server_port, int32_t session_count);
	virtual ~Server(void);

	void Start(int thread_pool_size = 0);
	void Stop(void);
	IoContext& GetIoService(void) { return io_context_; };

private:
	void CreateThreadPool(void);

public:
	static std::shared_ptr<Server<T>> server_instance_;
	static void SetServerInstance(std::shared_ptr<Server<T>> server_instance) { server_instance_ = server_instance; }
	static std::shared_ptr<Server<T>>& GetServerInstance(void) { return server_instance_; }

private:
	IoContext io_context_;
	BasicAcceptor<BasicSocket> acceptor_;

	boost::thread_group io_thread_group_;

	uint32_t thread_pool_size_;
	ObjectPool<std::shared_ptr<BasicSocket>> session_pool_;
};

template<typename T>
std::shared_ptr<Server<T>> Server<T>::server_instance_ = nullptr;

template<typename T>
Server<T>::Server(int32_t server_port, int32_t max_session_count)
	: acceptor_(io_context_, session_pool_, server_port)
	, thread_pool_size_(0)
{
	LL_INFO("Server Port:[%d]", server_port);
	LL_INFO("Max Session Count:[%d]", max_session_count);
	LL_INFO("Use ECHO Test Mode:[%s]", ConfigManager::GetInstance()->GetString("DServer", "USE_ECHO_TEST").c_str());
	
	for (int32_t i = 0; i < max_session_count; ++i)
	{
		std::shared_ptr<BasicSocket> object_ptr = std::make_shared<T>(io_context_, session_pool_);
		session_pool_.PushObject(object_ptr);
	}
}

template<typename T>
Server<T>::~Server(void)
{
	Stop();
}

template<typename T>
void Server<T>::Start(int thread_pool_size /* = 0 */)
{
	thread_pool_size_ = thread_pool_size;

	acceptor_.Start();

	CreateThreadPool();

	LL_DEBUG("Server Start");
}

template<typename T>
void Server<T>::Stop(void)
{
	acceptor_.Stop();
	io_context_.stop();
	io_thread_group_.join_all();
}

template<typename T>
void Server<T>::CreateThreadPool(void)
{
	if (0 == thread_pool_size_)
		thread_pool_size_ = (std::max)(static_cast<int32_t>(boost::thread::hardware_concurrency()), 1);

	for (int32_t i = 0; i < static_cast<int32_t>(thread_pool_size_); ++i)
	{
		boost::thread io_thread(boost::bind(&boost::asio::io_context::run, &io_context_));
		io_thread_group_.add_thread(&io_thread);
	}

	LL_DEBUG("Created Thread. [%d]", thread_pool_size_);
}
