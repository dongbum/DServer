#pragma once



class GameSocket : public BasicSocket, public GameProtocol
{
public:
	GameSocket(IoService& io_service)
		: BasicSocket(io_service)
	{

	};

	void OnPacket(void)
	{
		std::cout << "GameSocket OnPacket" << std::endl;
		
		// bool BaseProtocol::ExecuteProtocol(std::shared_ptr<BasicSocket> socket, uint32_t protocol_no, unsigned char * data, uint32_t data_length)
		ExecuteProtocol(shared_from_this(), 1, GetBufferManager().GetBuffer(), 12);
	};

private:
};
