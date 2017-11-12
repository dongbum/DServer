
#include "../dserver/define.h"
#include "game_socket.h"
#include "game_server.h"


GameServer::GameServer(void)
{
}

GameServer::~GameServer(void)
{
}

void GameServer::Start(void)
{
	__super::Start(8);
}
