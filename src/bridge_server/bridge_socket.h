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
		Header header;
		memcpy(&header, packet, sizeof(Header));

		if (header.GetTotalLength() != size)
		{
			LL_DEBUG("Invalid packet size. total:[%d] size:[%d]", header.GetTotalLength(), size);
			OnClose();
			return;
		}

		if (header.GetDataLength() < 0 || header.GetDataLength() > (size - static_cast<int>(sizeof(Header))) || header.GetDataLength() > RECV_BUFFER_SIZE)
		{
			LL_DEBUG("Invalid packet data length:[%d]", header.GetDataLength());
			OnClose();
			return;
		}

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
