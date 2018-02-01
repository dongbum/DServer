#pragma once

class MSSQLConnPool : public TCWrapper
{
public:
	MSSQLConnPool(int32_t& nMaxThreadCnt, int32_t nMaxQueryCnt);
	virtual ~MSSQLConnPool(void);

	bool		Init(TCHAR* connection_string);
	MSSQLConn*	GetOdbcConn(int32_t type);

protected:
	void		Clear(void);

protected:
	MSSQLConn**		mssql_conns_;
	int32_t			max_thread_count_;
	int32_t			max_query_count_;
	TCHAR			connetion_string_[MAX_STRING_LENGTH];
};
