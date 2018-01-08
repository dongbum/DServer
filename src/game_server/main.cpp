#include "define.h"

int main(void)
{
	if (false == CONFIG_MANAGER_INSTANCE.Initialize("GameServerConfig.ini"))
		return 0;

	if (false == LOG_MANAGER_INSTANCE.Init())
		return 0;

	std::shared_ptr<GameServer> game_server(new GameServer);
	GameServer::SetServerInstance(std::static_pointer_cast<Server<GameSocket>>(game_server));
	game_server->Start();

	while (true)
		getchar();

	return 0;
}