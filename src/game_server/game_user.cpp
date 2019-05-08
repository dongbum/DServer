#include "define.h"

GameUser::GameUser(IoContext& io_context, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool)
	: GameSocket(io_context, session_pool)
	, usn_(0)
{
	memset(user_id_, 0, USER_ID_LEN);
}

GameUser::~GameUser(void)
{

}