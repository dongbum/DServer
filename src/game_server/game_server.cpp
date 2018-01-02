#include "game_server.h"


GameServer::GameServer(void)
	: Server(
		CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "GAME_PORT"),
		CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "MAX_SESSION_COUNT")
	)
	, bridge_conn_(__super::GetIoService())
{
}

GameServer::~GameServer(void)
{
}

void GameServer::Start(void)
{
	int32_t thread_count = CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "THREAD_COUNT");

	__super::Start(thread_count);

	bridge_conn_.Connect("127.0.0.1", 30000);
}
