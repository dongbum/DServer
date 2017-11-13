#include "game_protocol.h"

GameProtocol::GameProtocol(void)
{
}

GameProtocol::~GameProtocol(void)
{
}

void GameProtocol::Init(void)
{
	BIND_PROTOCOL(1, &GameProtocol::Echo);
	AddProtocol(1, boost::bind(&GameProtocol::Echo, this, _1, _2, _3, _4));
}

uint32_t GameProtocol::Echo(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length)
{


	return 0;
}
