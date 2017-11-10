#include "game_server/game_server.h"

int main(void)
{
	/*
	Header header;
	header.total_length_ = 1;
	header.protocol_no_ = 2;
	header.data_length_ = 3;

	std::vector<char> buffer_(1024);
	memcpy(&buffer_[0], &header, sizeof(header));

	memmove(&buffer_[0], &buffer_[4], buffer_.size() - 4);

	return 0;
	*/

	GameServer game_server;
	game_server.Start();

	while (true)
		getchar();

	return 0;
}