#pragma once

template<typename T>
class Server
{
public:
	Server(void);
	virtual ~Server(void);

	void Start(int thread_pool_size);
	void Stop(void);

private:
	void CreateThreadPool(void);

private:
	IoService io_service_;
	std::shared_ptr<Work> work_ptr_;
	BasicAcceptor<T> acceptor_;

	boost::thread_group io_thread_group_;

	uint32_t thread_pool_size_;
};



template<typename T>
Server<T>::Server(void)
	: acceptor_(io_service_, 20000)
	, work_ptr_(new Work(io_service_))
	, thread_pool_size_(0)
{
}

template<typename T>
Server<T>::~Server(void)
{
	Stop();
}

template<typename T>
void Server<T>::Start(int thread_pool_size)
{
	acceptor_.Start();

	CreateThreadPool();
}

template<typename T>
void Server<T>::Stop(void)
{
	acceptor_.Stop();
	io_service_.stop();
	io_thread_group_.join_all();
}

template<typename T>
void Server<T>::CreateThreadPool(void)
{
	if (0 == thread_pool_size_)
		thread_pool_size_ = (std::max)(static_cast<int32_t>(boost::thread::hardware_concurrency()), 1);

	for (int32_t i = 0; i < static_cast<int32_t>(thread_pool_size_); ++i)
	{
		boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
		io_thread_group_.add_thread(&io_thread);
	}
}
