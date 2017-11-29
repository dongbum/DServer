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
	
	char send_buffer[SEND_BUFFER_SIZE] = { 0, };
	int index = 0;

	int test = 7;

	Header send_header;
	send_header.SetDataLength(4);
	send_header.SetTotalLength(16);

	memcpy(&send_buffer[index], &send_header, sizeof(send_header));
	index += sizeof(send_header);
	memcpy(&send_buffer[index], &test, sizeof(test));
	index += sizeof(test);

	int send_length = index;

	session->OnSend(send_length, send_buffer);

	return 0;
}
