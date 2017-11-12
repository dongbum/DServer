#pragma once

#include "../dserver/base_protocol.h"

/*
#define BIND_PROTOCOL(PROTOCOL_NO, FUNC) \
	AddProtocol(PROTOCOL_NO, boost::bind(FUNC, _1, _2, _3, _4))
*/


class GameProtocol : public BaseProtocol
{
public:
	GameProtocol(void);
	virtual ~GameProtocol(void);

	void Init(void);

private:

};