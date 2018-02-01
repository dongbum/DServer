#pragma once

class GameUser : public GameSocket
{
public:
	GameUser(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool);
	virtual ~GameUser(void);

	uint64_t&	GetUSN(void) { return usn_; };
	void		SetUSN(uint64_t usn) { usn_ = usn; };

	char*		GetUserID(void) { return user_id_; };
	void		SetUserID(char* user_id) { strncpy_s(user_id_, user_id, USER_ID_LEN); };

private:
	uint64_t		usn_;
	char			user_id_[USER_ID_LEN];

};
