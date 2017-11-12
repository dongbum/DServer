#pragma once

#include "game_socket.h"
#include "game_protocol.h"

class GameServer : public Server<GameSocket>
{
public:
	GameServer(void);
	virtual ~GameServer(void);

	void Start(void);

private:

};
