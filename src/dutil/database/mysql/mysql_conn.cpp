#include "../../define.h"


MySQLConn::MySQLConn(void)
	: driver_(nullptr), conn_(nullptr), pstmt_(nullptr), resultset_(nullptr)
	, param_index_(1), column_index_(1)
{
	
}


MySQLConn::~MySQLConn(void)
{
	Disconnect();
}


bool MySQLConn::Connect(void)
{
	try
	{
		driver_ = get_driver_instance();

		conn_ = driver_->connect(sql::SQLString("tcp://127.0.0.1:3306"), sql::SQLString("account"), sql::SQLString("password"));
	}
	catch (sql::SQLException& ex)
	{
		LL_DEBUG("SQLException [%d]", ex.getErrorCode());
		Disconnect();
		return false;
	}

	return true;
}


void MySQLConn::Disconnect(void)
{
	if (nullptr != resultset_)
	{
		delete resultset_;
		resultset_ = nullptr;
	}

	if (nullptr != pstmt_)
	{
		delete pstmt_;
		pstmt_ = nullptr;
	}	

	if (nullptr != conn_)
	{
		delete conn_;
		conn_ = nullptr;
	}
}


void MySQLConn::PrepareQuery(char* query_info)
{
	param_index_ = 0;
	pstmt_ = conn_->prepareStatement(sql::SQLString(query_info));
}


void MySQLConn::BindParam(const int32_t value)
{
	pstmt_->setInt(param_index_, value);
	++param_index_;
}


void MySQLConn::BindParam(const int64_t value)
{
	pstmt_->setInt64(param_index_, value);
	++param_index_;
}


void MySQLConn::BindParam(const uint32_t value)
{
	pstmt_->setUInt(param_index_, value);
	++param_index_;
}


void MySQLConn::BindParam(const uint64_t value)
{
	pstmt_->setUInt64(param_index_, value);
	++param_index_;
}


void MySQLConn::BindParam(const double value)
{
	pstmt_->setDouble(param_index_, value);
	++param_index_;
}

#ifdef _WIN32
void MySQLConn::BindParam(const SYSTEMTIME value)
{
	char temp[1024] = { 0, };
	_snprintf_s(temp, MAX_DATETIME_SIZE, _TRUNCATE, "%d-%02d-%02d %02d:%02d:%02d"
		, value.wYear, value.wMonth, value.wDay
		, value.wHour, value.wMinute, value.wSecond);

	pstmt_->setDateTime(param_index_, sql::SQLString(temp));
	++param_index_;
}
#endif

void MySQLConn::BindParam(const char* value)
{
	pstmt_->setString(param_index_, sql::SQLString(value));
	++param_index_;
}


void MySQLConn::BindParam(const bool value)
{
	pstmt_->setBoolean(param_index_, value);
	++param_index_;
}


int32_t MySQLConn::GetInt(void)
{
	return resultset_->getInt(column_index_++);
}


int64_t MySQLConn::GetInt64(void)
{
	return resultset_->getInt64(column_index_++);
}


uint32_t MySQLConn::GetUInt(void)
{
	return resultset_->getUInt(column_index_++);
}


uint64_t MySQLConn::GetUInt64(void)
{
	return resultset_->getUInt64(column_index_++);
}


double MySQLConn::GetDouble(void)
{
	return resultset_->getDouble(column_index_++);
}


const char* MySQLConn::GetString(void)
{
	sql::SQLString result_str = resultset_->getString(column_index_++);
	return result_str.c_str();
}


bool MySQLConn::GetBool(void)
{
	return resultset_->getBoolean(column_index_++);
}


void MySQLConn::Execute(void)
{
	resultset_ = pstmt_->executeQuery();
}


bool MySQLConn::Fetch(void)
{
	return resultset_->next();
}
