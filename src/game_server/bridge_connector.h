#pragma once

class BridgeConnector : public BasicConnector, public BridgeProtocol
{
public:
	BridgeConnector(IoService& io_service)
		: BasicConnector(io_service)
	{

	};

	virtual ~BridgeConnector(void)
	{

	};

	void OnPacket(char* packet, int size) override
	{
		// std::cout << "GameSocket OnPacket size:" << size << std::endl;
		Header header;
		memcpy(&header, packet, sizeof(Header));

		// std::cout << "Header.TotalLength : " << header.GetTotalLength() << std::endl;
		// std::cout << "Header.ProtocolNo : " << header.GetProtocolNo() << std::endl;
		// std::cout << "Header.DataLength : " << header.GetDataLength() << std::endl;

		char body[RECV_BUFFER_SIZE] = { 0, };
		memcpy(body, &packet[sizeof(Header)], header.GetDataLength());

		ExecuteProtocol(shared_from_this(), header.protocol_no_, body, header.data_length_);
	};

private:
};
