#include "dserver/define.h"
#include "game_server/game_server.h"

int main(void)
{
	if (false == CONFIG_MANAGER_INSTANCE.Initialize("D:\\Work\\DServer2.git\\vs_solution\\Bin\\ServerConfig.ini"))
		return 0;

	if (false == LOG_MANAGER_INSTANCE.Init())
		return 0;

	GameServer game_server;
	game_server.Start();

	while (true)
		getchar();

	return 0;
}