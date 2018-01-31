#pragma once

class GameUser : public GameSocket
{
public:
	GameUser(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool)
		: GameSocket(io_service, session_pool)
	{

	};

	virtual ~GameUser(void)
	{

	};

private:
	uint64_t	usn_;

};
