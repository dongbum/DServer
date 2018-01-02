#pragma once

#include "protocol/game_protocol.h"
#include "game_socket.h"
#include "bridge_connector.h"

class GameServer : public Server<GameSocket>
{
public:
	GameServer(void);
	virtual ~GameServer(void);

	void Start(void);

private:
	BridgeConnector bridge_conn_;
};
