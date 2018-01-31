#include "define.h"

GameUser::GameUser(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool)
	: GameSocket(io_service, session_pool)
{

}

GameUser::~GameUser(void)
{

}