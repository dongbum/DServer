#include "GameServer.h"

int main(void)
{
	GameServer game_server;
	game_server.Start();

	while (true)
		getchar();

	return 0;
}