#include "bridge_server.h"

int main(void)
{
	if (false == ConfigManager::GetInstance()->Initialize("BridgeServerConfig.ini"))
		return 0;

	if (false == LogManager::GetInstance()->Init())
		return 0;

	BridgeServer bridge_server;
	bridge_server.Start();

	while (true)
		getchar();

	return 0;
}