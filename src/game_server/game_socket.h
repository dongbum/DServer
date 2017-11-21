#pragma once



class GameSocket : public BasicSocket, public GameProtocol
{
public:
	GameSocket(IoService& io_service)
		: BasicSocket(io_service)
	{
		__super::InitProtocol();
	};

	void OnPacket(char* packet, int size)
	{
		std::cout << "GameSocket OnPacket size:" << size << std::endl;
		Header header;

		std::cout << "Header.TotalLength : " << header.total_length_ << std::endl;
		std::cout << "Header.ProtocolNo : " << header.protocol_no_ << std::endl;
		std::cout << "Header.DataLength : " << header.data_length_ << std::endl;

		char body[RECV_BUFFER_SIZE] = { 0, };

		ExecuteProtocol(shared_from_this(), header.protocol_no_, body, header.data_length_);
	};

};
