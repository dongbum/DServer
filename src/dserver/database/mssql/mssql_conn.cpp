#include "../../define.h"


MSSQLConn::MSSQLConn(void)
	: henv_(nullptr)
	, hdbc_(nullptr)
	, hstmt_(nullptr)
{

}

MSSQLConn::~MSSQLConn(void)
{
	Disconnect();
}

bool MSSQLConn::Connect(TCHAR* connection_string)
{
	TCHAR			output[DB_BUFFER_SIZE] = { 0, };
	SQLSMALLINT		nOutLen;
	SQLRETURN		ret;

	if (hdbc_)
		return true;

	if (false == InitEnvHandle())
		return false;

	if (false == InitConnectHandle())
		return false;

	ret = SQLDriverConnect(hdbc_, NULL, connection_string, (SQLSMALLINT)_tcslen(connection_string), output, DB_BUFFER_SIZE, &nOutLen, SQL_DRIVER_NOPROMPT);

	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
		return false;

	if (false == InitStmtHandle())
		return false;

	return true;
}

void MSSQLConn::Disconnect(void)
{
	if (hstmt_)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt_);
		hstmt_ = nullptr;
	}

	if (hdbc_)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc_);
		hdbc_ = nullptr;
	}

	if (henv_)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, henv_);
		henv_ = nullptr;
	}
}

bool MSSQLConn::InitEnvHandle(void)
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv_))
		return false;

	if (SQL_SUCCESS != SQLSetEnvAttr(henv_, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER))
		return false;

	return true;
}

bool MSSQLConn::InitConnectHandle(void)
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, henv_, &hdbc_))
		return false;

	if (SQL_SUCCESS != SQLSetConnectAttr(hdbc_, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)DEFAULT_LOGIN_TIMEOUT, 0))
		return false;

	if (SQL_SUCCESS != SQLSetConnectAttr(hdbc_, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)DEFAULT_CONNECTION_TIMEOUT, 0))
		return false;

	return true;
}

bool MSSQLConn::InitStmtHandle(void)
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, hdbc_, (SQLHSTMT*)&hstmt_))
		return false;

	if (SQL_SUCCESS != SQLSetStmtAttr(hstmt_, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_READ_ONLY, 0))
		return false;

	if (SQL_SUCCESS != SQLSetStmtAttr(hstmt_, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)DEFAULT_QUERY_TIMEOUT, 0))
		return false;

	return true;
}
