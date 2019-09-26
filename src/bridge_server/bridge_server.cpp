#include "bridge_server.h"

BridgeServer::BridgeServer(void)
	: Server(
		ConfigManager::GetInstance()->GetInt32("DServer", "GAME_PORT"),
		ConfigManager::GetInstance()->GetInt32("DServer", "MAX_SESSION_COUNT")
	)
{
}

BridgeServer::~BridgeServer(void)
{
}

void BridgeServer::Start(void)
{
	int32_t thread_count = ConfigManager::GetInstance()->GetInt32("DServer", "THREAD_COUNT");

	BaseClass::Start(thread_count);
}
