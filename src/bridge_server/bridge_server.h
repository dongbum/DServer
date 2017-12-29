#pragma once

#include "protocol/bridge_protocol.h"
#include "bridge_socket.h"

class BridgeServer : public Server<BridgeSocket>
{
public:
	BridgeServer(void);
	virtual ~BridgeServer(void);

	void Start(void);

private:

};
