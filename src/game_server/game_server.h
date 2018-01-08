#pragma once

class GameServer : public Server<GameSocket>
{
public:
	GameServer(void);
	virtual ~GameServer(void);

	void Start(void);

	BridgeConnector* GetBridgeConn(void)	{ return bridge_conn_; }

private:
	BridgeConnector* bridge_conn_;
};
