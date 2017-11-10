#pragma once

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

	BasicAcceptor<BasicSocket> acceptor_;

	boost::thread_group io_thread_group_;
};
