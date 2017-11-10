#pragma once

#include "dserver/define.h"
#include "game_socket.h"

class GameServer : public Server<GameSocket>
{
public:
	GameServer(void);
	virtual ~GameServer(void);

	void Start(void);

private:

};
