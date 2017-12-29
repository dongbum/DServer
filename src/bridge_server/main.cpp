#include "bridge_server.h"

int main(void)
{
	if (false == CONFIG_MANAGER_INSTANCE.Initialize("ServerConfig.ini"))
		return 0;

	if (false == LOG_MANAGER_INSTANCE.Init())
		return 0;

	BridgeServer bridge_server;
	bridge_server.Start();

	while (true)
		getchar();

	return 0;
}