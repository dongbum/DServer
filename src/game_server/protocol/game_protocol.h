#pragma once

#define BIND_PROTOCOL(PROTOCOL_NO, FUNC) \
	AddProtocol(PROTOCOL_NO, boost::bind(FUNC, this, _1, _2, _3, _4))

class GameProtocol : public BaseProtocol
{
public:
	GameProtocol(void);
	virtual ~GameProtocol(void);

	void InitProtocol(void);

	uint32_t Echo(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length);
	uint32_t ChattingReq(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length);

private:

};