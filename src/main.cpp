#include "dserver/define.h"
#include "game_server/game_server.h"

int main(void)
{
	GameServer game_server;
	game_server.Start();

	while (true)
		getchar();

	return 0;
}