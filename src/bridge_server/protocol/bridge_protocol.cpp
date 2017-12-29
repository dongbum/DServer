#include "bridge_protocol_define.h"
#include "bridge_protocol.h"

BridgeProtocol::BridgeProtocol(void)
{
}

BridgeProtocol::~BridgeProtocol(void)
{
}

void BridgeProtocol::InitProtocol(void)
{
	AddProtocol(BRIDGE_PROTOCOL_ECHO, boost::bind(&BridgeProtocol::Echo, this, _1, _2, _3, _4));

	BIND_PROTOCOL(BRIDGE_PROTOCOL_ECHO, &BridgeProtocol::Echo);
}

uint32_t BridgeProtocol::Echo(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length)
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
