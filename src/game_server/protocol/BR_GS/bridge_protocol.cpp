#include "../../define.h"

BridgeProtocol::BridgeProtocol(void)
{
}

BridgeProtocol::~BridgeProtocol(void)
{
}

void BridgeProtocol::InitProtocol(void)
{
	BIND_PROTOCOL(CL_GS_PROTOCOL::CL_GS_CHATTING_RES, &BridgeProtocol::ChattingRes);
}

uint32_t BridgeProtocol::ChattingRes(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length)
{
	//std::cout << "Protocol Echo" << std::endl;

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
