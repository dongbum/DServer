#include "define.h"

GameServer::GameServer(void)
	: Server(
		CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "GAME_PORT"),
		CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "MAX_SESSION_COUNT")
	)
	, bridge_conn_(new BridgeConnector(BaseClass::GetIoService()))
{

}

GameServer::~GameServer(void)
{

}

void GameServer::Start(void)
{
	LL_DEBUG("GameServer Start");

	int32_t thread_count = CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "THREAD_COUNT");

	BaseClass::Start(thread_count);

	bridge_conn_->Connect(
		CONFIG_MANAGER_INSTANCE.GetString("BRIDGE_SERVER", "IP"),
		CONFIG_MANAGER_INSTANCE.GetInt32("BRIDGE_SERVER", "PORT"));
}
