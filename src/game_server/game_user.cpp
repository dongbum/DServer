#include "define.h"

GameUser::GameUser(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool)
	: GameSocket(io_service, session_pool)
	, usn_(0)
{
	memset(user_id_, 0, USER_ID_LEN);
}

GameUser::~GameUser(void)
{

}