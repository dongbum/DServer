#pragma once

#include "../../dnetwork/protocol/base_protocol.h"

#define BIND_PROTOCOL(PROTOCOL_NO, FUNC) \
	AddProtocol(PROTOCOL_NO, boost::bind(FUNC, this, _1, _2, _3, _4))

class BridgeProtocol : public BaseProtocol
{
public:
	BridgeProtocol(void);
	virtual ~BridgeProtocol(void);

	void InitProtocol(void);

	uint32_t Echo(std::shared_ptr<BasicSocket> session, uint32_t& protocol_no, char* data, uint32_t data_length);

private:

};