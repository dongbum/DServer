#include "define.h"

int main(void)
{
	if (false == ConfigManager::GetInstance()->Initialize("GameServerConfig.ini"))
		return 0;

	if (false == LogManager::GetInstance()->Init())
		return 0;

#ifdef _WIN32
	Minidump::Init(
		ConfigManager::GetInstance()->GetString("DServer", "DUMP_PATH"),
		ConfigManager::GetInstance()->GetString("DServer", "DUMP_FILENAME"));
#endif

	std::shared_ptr<GameServer> game_server(new GameServer);
	GameServer::SetServerInstance(std::static_pointer_cast<Server<GameUser>>(game_server));
	game_server->Start();

	while (true)
		getchar();

	return 0;
}