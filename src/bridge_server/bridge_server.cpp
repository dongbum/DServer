#include "bridge_server.h"

BridgeServer::BridgeServer(void)
	: Server(
		CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "GAME_PORT"),
		CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "MAX_SESSION_COUNT")
	)
{
}

BridgeServer::~BridgeServer(void)
{
}

void BridgeServer::Start(void)
{
	int32_t thread_count = CONFIG_MANAGER_INSTANCE.GetInt32("DServer", "THREAD_COUNT");

	__super::Start(thread_count);
}
