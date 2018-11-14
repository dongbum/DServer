#include "../../define.h"

MSSQLConnPool::MSSQLConnPool(int32_t& max_thread_count, int32_t max_query_count)
	: max_thread_count_(max_thread_count), max_query_count_(max_query_count)
{
	mssql_conns_ = new MSSQLConn*[max_thread_count_];
	for (int32_t i = 0; i<max_thread_count_; ++i)
		mssql_conns_[i] = nullptr;

	wmemset(connetion_string_, 0, MAX_STRING_LENGTH);
}


MSSQLConnPool::~MSSQLConnPool(void)
{
	Clear();
	SAFE_DELETE_ARRAY(mssql_conns_);
	max_thread_count_ = 0;
	max_query_count_ = 0;
}


bool MSSQLConnPool::Init(TCHAR* connection_string)
{
	Clear();

	_tcsncpy_s(&connetion_string_[0], MAX_STRING_LENGTH, connection_string, _TRUNCATE);
	for (int32_t i = 0; i<max_thread_count_; ++i)
	{
		mssql_conns_[i] = new MSSQLConn(max_query_count_);
		if (!mssql_conns_[i]->Connect(connetion_string_))
		{
			Clear();
			return false;
		}
	}

	return true;
}


MSSQLConn* MSSQLConnPool::GetOdbcConn(int32_t type)
{
	MSSQLConn* mssql_conn = mssql_conns_[type];

	if (!mssql_conn || mssql_conn->IsConnDead())
	{
		if (nullptr != mssql_conn)
			SAFE_DELETE(mssql_conn);

		mssql_conn = new MSSQLConn(max_query_count_);
		if (!mssql_conn->Connect(connetion_string_))
		{
			SAFE_DELETE(mssql_conn);
			return nullptr;
		}
	}

	return mssql_conn;
}


void MSSQLConnPool::Clear(void)
{
	for (int32_t i = 0; i<max_thread_count_; ++i)
		SAFE_DELETE(mssql_conns_[i]);
}
