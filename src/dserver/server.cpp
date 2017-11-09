#include "define.h"

Server::Server(void)
	: acceptor_(io_service_, 20000)
{
}

Server::~Server(void)
{
}

void Server::Start(int thread_pool_size)
{
	acceptor_.Start();

	CreateThreadPool();
}

void Server::Stop(void)
{
	acceptor_.Stop();
	io_thread_group_.join_all();
}

void Server::CreateThreadPool(void)
{
	int32_t thread_count = 8;
	if (0 == thread_count)
		thread_count = (std::max)(static_cast<int32_t>(boost::thread::hardware_concurrency()), 1);

	for (int32_t i = 0; i < thread_count; ++i)
	{
		boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
		io_thread_group_.add_thread(&io_thread);
	}
}
