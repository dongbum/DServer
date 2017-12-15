#include "game_protocol_define.h"
#include "game_protocol.h"

GameProtocol::GameProtocol(void)
{
}

GameProtocol::~GameProtocol(void)
{
}

void GameProtocol::InitProtocol(void)
{
	AddProtocol(GAME_PROTOCOL_ECHO, boost::bind(&GameProtocol::Echo, this, _1, _2, _3, _4));

	BIND_PROTOCOL(GAME_PROTOCOL_ECHO, &GameProtocol::Echo);
}

uint32_t GameProtocol::Echo(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length)
{
	//std::cout << "Protocol Echo" << std::endl;
	
	int test = 7;

	Header send_header;
	send_header.SetDataLength(4);
	send_header.SetTotalLength(16);

	Packet packet;
	packet << send_header;
	packet << test;

	session->OnSend(packet.GetSize(), packet.GetBuffer());

	return 0;
}
