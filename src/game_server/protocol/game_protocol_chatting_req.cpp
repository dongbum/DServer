#include "game_protocol.h"

uint32_t GameProtocol::ChattingReq(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length)
{
	int test = 7;

	Header send_header;
	send_header.SetDataLength(4);
	send_header.SetTotalLength(16);

	Packet packet;
	packet << send_header;
	packet << test;

	session->OnSend(static_cast<int>(packet.GetSize()), packet.GetBuffer());

	return 0;
}
