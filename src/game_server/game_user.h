#pragma once

class GameUser : public GameSocket
{
public:
	GameUser(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool);
	virtual ~GameUser(void);

	uint64_t&	GetUSN(void) { return usn_; };
	void		SetUSN(uint64_t usn) { usn_ = usn; };

private:
	uint64_t	usn_;

};
