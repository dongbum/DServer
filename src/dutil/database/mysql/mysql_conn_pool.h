#pragma once

class MySQLConnPool
{
public:
	typedef std::shared_ptr<MySQLConn>		MySQLConnPtr;

	explicit MySQLConnPool(int32_t& pool_count);
	virtual ~MySQLConnPool(void);

	bool			Init(void);
	void			Clear(void);
	MySQLConnPtr	GetMySQLConn(void);

private:
	std::vector<MySQLConnPtr>	mysql_conn_vec_;
	int32_t						pool_count_;
};
