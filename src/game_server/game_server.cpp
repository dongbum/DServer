#include "define.h"

GameServer::GameServer(void)
	: Server(
		ConfigManager::GetInstance()->GetInt32("DServer", "GAME_PORT"),
		ConfigManager::GetInstance()->GetInt32("DServer", "MAX_SESSION_COUNT")
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

	int32_t thread_count = ConfigManager::GetInstance()->GetInt32("DServer", "THREAD_COUNT");

	BaseClass::Start(thread_count);

	bridge_conn_->Connect(
		ConfigManager::GetInstance()->GetString("BRIDGE_SERVER", "IP"),
		ConfigManager::GetInstance()->GetInt32("BRIDGE_SERVER", "PORT"));
}
