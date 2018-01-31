#pragma once

class GameServer : public Server<GameUser>
{
public:
	GameServer(void);
	virtual ~GameServer(void);

	void Start(void);

	std::shared_ptr<BridgeConnector>& GetBridgeConn(void)	{ return bridge_conn_; }

private:
	std::shared_ptr<BridgeConnector> bridge_conn_;
};
