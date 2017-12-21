#pragma once

#define	DB_BUFFER_SIZE		2048

class MSSQLConn
{
public:
	MSSQLConn(void);
	virtual ~MSSQLConn(void);

	bool Connect(TCHAR* connection_string);
	void Disconnect(void);

private:
	bool InitEnvHandle(void);
	bool InitConnectHandle(void);
	bool InitStmtHandle(void);

private:
	SQLHENV		henv_;
	SQLHDBC		hdbc_;
	SQLHSTMT	hstmt_;

};
