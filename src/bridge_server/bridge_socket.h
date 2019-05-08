#pragma once



class BridgeSocket : public BasicSocket, public BridgeProtocol
{
public:
	BridgeSocket(IoContext& io_context, ObjectPool<std::shared_ptr<BasicSocket>>& session_pool)
		: BasicSocket(io_context)
		, session_pool_(session_pool)
	{
		BridgeProtocol::InitProtocol();
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

	void OnClose(void) override
	{
		LL_DEBUG("GameSocket OnClose");

		BasicSocket::OnClose();
		session_pool_.ReleasePoolObject(shared_from_this());
	};
private:
	ObjectPool<std::shared_ptr<BasicSocket>>& session_pool_;
};
