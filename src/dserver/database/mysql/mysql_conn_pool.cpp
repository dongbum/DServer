#include "../../define.h"


MySQLConnPool::MySQLConnPool(int32_t& pool_count)
	: pool_count_(pool_count)
{
	for (int32_t i = 0; i < pool_count_; ++i)
	{
		mysql_conn_vec_.push_back(MySQLConnPtr(new MySQLConn));
	}
}


MySQLConnPool::~MySQLConnPool(void)
{
	Clear();
}


bool MySQLConnPool::Init(void)
{
	for (int32_t i = 0; i < pool_count_; ++i)
	{
		if (false == mysql_conn_vec_[i]->Connect())
		{
			Clear();
			return false;
		}
	}

	return true;
}


void MySQLConnPool::Clear(void)
{
	mysql_conn_vec_.clear();
}


MySQLConnPool::MySQLConnPtr MySQLConnPool::GetMySQLConn(void)
{
	MySQLConnPtr mysql_conn = mysql_conn_vec_[0];

	return mysql_conn;
}
