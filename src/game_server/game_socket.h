#pragma once

class GameSocket : public BasicSocket
{
public:
	GameSocket(IoService& io_service)
		: BasicSocket(io_service)
	{

	};

	void OnPacket(void)
	{
		std::cout << "GameSocket OnPacket" << std::endl;
	};

private:
};
