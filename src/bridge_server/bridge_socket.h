#pragma once



class BridgeSocket : public BasicSocket, public BridgeProtocol
{
public:
	BridgeSocket(IoService& io_service, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool)
		: BasicSocket(io_service)
		, session_pool_(session_pool)
	{
		__super::InitProtocol();
	};

	void OnPacket(char* packet, int size)
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

	void OnClose(void)
	{
		LL_DEBUG("GameSocket OnClose");

		__super::OnClose();
		session_pool_.ReleasePoolObject(shared_from_this());
	};
private:
	ObjectPool<std::shared_ptr<BasicSocket>>& session_pool_;
};
