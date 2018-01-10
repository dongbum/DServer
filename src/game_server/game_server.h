#pragma once

class GameServer : public Server<GameSocket>
{
public:
	GameServer(void);
	virtual ~GameServer(void);

	void Start(void);

	std::shared_ptr<BridgeConnector>& GetBridgeConn(void)	{ return bridge_conn_; }

private:
	std::shared_ptr<BridgeConnector> bridge_conn_;
};
