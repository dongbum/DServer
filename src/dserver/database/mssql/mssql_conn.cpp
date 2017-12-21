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
	SQLSMALLINT		outlen;
	SQLRETURN		ret;

	if (hdbc_)
		return true;

	if (false == InitEnvHandle())
		return false;

	if (false == InitConnectHandle())
		return false;

	ret = SQLDriverConnect(hdbc_, NULL, connection_string, (SQLSMALLINT)_tcslen(connection_string), output, DB_BUFFER_SIZE, &outlen, SQL_DRIVER_NOPROMPT);

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

bool MSSQLConn::PrepareQuery(uint16_t query_type, TCHAR * query_info)
{
	ClearStmt();

	SQLRETURN ret = SQL_ERROR;

	param_num_ = 0;
	col_num_ = 0;
	query_num_ = query_type;

	ret = SQLPrepare(hstmt_, query_info, SQL_NTSL);

	if (SQL_SUCCESS != ret)
	{
		TCHAR message[SQL_MAX_MESSAGE_LENGTH] = { 0, };
		GetDBEErrorMessage(SQL_HANDLE_STMT, hstmt_, message);
		LL_DEBUG("Failed to Prepare Query, QueryType[%s]", message);
	}

	SetDescribeParam();

	return false;
}

bool MSSQLConn::BindParamInput(void * value)
{
	SQLRETURN nRet = SQL_ERROR;

	DESC_PARAM& desc_param = query_desc_param_vec_[query_num_].desc_param_vec[param_num_];
	nRet = SQLBindParameter(hstmt_, ++param_num_, SQL_PARAM_INPUT, desc_param.cdata_type, desc_param.sql_data_type,
		desc_param.param_size, 0, value, desc_param.param_size, (SQLLEN*)&desc_param.param_size);

	if (SQL_SUCCESS != nRet)
	{
		TCHAR szMessage[SQL_MAX_MESSAGE_LENGTH] = { 0, };
		GetDBEErrorMessage(SQL_HANDLE_STMT, hstmt_, szMessage);
		LL_DEBUG("Failed to Bind Parameter Input, SQLBindParameter[%s]", szMessage);
		return false;
	}

	return true;
}

bool MSSQLConn::BindParamOutput(void * value)
{
	SQLRETURN nRet = SQL_ERROR;

	DESC_PARAM& desc_param = query_desc_param_vec_[query_num_].desc_param_vec[param_num_];
	nRet = SQLBindParameter(hstmt_, ++param_num_, SQL_PARAM_OUTPUT, desc_param.cdata_type, desc_param.sql_data_type,
		desc_param.param_size, 0, value, desc_param.param_size, (SQLLEN*)&desc_param.param_size);

	if (SQL_SUCCESS != nRet)
	{
		TCHAR szMessage[SQL_MAX_MESSAGE_LENGTH] = { 0, };
		GetDBEErrorMessage(SQL_HANDLE_STMT, hstmt_, szMessage);
		LL_DEBUG("Failed to Bind Parameter Input, SQLBindParameter[%s]", szMessage);
		return false;
	}

	return true;
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

void MSSQLConn::ClearStmt(void)
{
	if (hstmt_)
	{
		SQLFreeStmt(hstmt_, SQL_UNBIND);
		SQLFreeStmt(hstmt_, SQL_RESET_PARAMS);
		SQLFreeStmt(hstmt_, SQL_CLOSE);
	}
}

void MSSQLConn::SetDescribeParam(void)
{
	SQLRETURN		ret = SQL_ERROR;
	SQLSMALLINT		param_count = 0;

	QUERY_DESC_PARAM& query_desc_param = query_desc_param_vec_[query_num_];
	if (!query_desc_param.desc_param_vec.empty())
		return;

	if (query_desc_param.is_no_data)
		return;

	ret = SQLNumParams(hstmt_, &param_count);
	if (SQL_SUCCESS != ret)
	{
		LL_DEBUG("Failed to Set Describe Param, SQLNumParams[%d]", query_num_);
		return;
	}

	if (0 == param_count)
	{
		query_desc_param.is_no_data = true;
		return;
	}

	query_desc_param.desc_param_vec.resize(param_count);

	for (int16_t i = 0; i<param_count; ++i)
	{
		DESC_PARAM& desc_param = query_desc_param.desc_param_vec[i];
		ret = SQLDescribeParam(hstmt_, i + 1, &desc_param.sql_data_type, &desc_param.param_size, &desc_param.decimal_digits, &desc_param.nullable);
		if (SQL_SUCCESS != ret)
		{
			LL_DEBUG("Failed to Set Describe Param, SQLDescribeParam[%d]", query_num_);
			return;
		}

		desc_param.cdata_type = GetCDataType(desc_param.sql_data_type);
		if (SQL_C_WCHAR == desc_param.cdata_type)
		{
			++desc_param.param_size;
			desc_param.param_size *= 2;
		}
	}
}

SQLSMALLINT MSSQLConn::GetCDataType(SQLSMALLINT sql_data_type)
{
	switch (sql_data_type)
	{
	case SQL_VARCHAR:
	case SQL_DECIMAL:
	case SQL_NUMERIC:
		return SQL_C_CHAR;
	case SQL_WVARCHAR:
	case SQL_WLONGVARCHAR:
		return SQL_C_WCHAR;
	case SQL_FLOAT:
		return SQL_C_FLOAT;
	case SQL_BIGINT:
		return SQL_C_SBIGINT;
	case SQL_DATETIME:
		return SQL_C_TIMESTAMP;
	}

	return sql_data_type;
}

TCHAR * MSSQLConn::GetDBEErrorMessage(const SQLSMALLINT nHandleType, const SQLHENV & hStatement, TCHAR szMessage[])
{
	SQLTCHAR		sql_state[SQL_MAX_MESSAGE_LENGTH] = { 0, };
	SQLTCHAR		message[SQL_MAX_MESSAGE_LENGTH] = { 0, };
	SQLINTEGER		error = 0;
	SQLSMALLINT		message_lengh = 0;

	if (SQL_SUCCESS != ::SQLGetDiagRec(nHandleType, hStatement, 1, sql_state, &error, message, SQL_MAX_MESSAGE_LENGTH, &message_lengh))
		return nullptr;

	_sntprintf_s(szMessage, SQL_MAX_MESSAGE_LENGTH, _TRUNCATE, _T("STATE[%s], ERROR[%ld], MSG[%s]"), sql_state, error, message);

	return &szMessage[0];
}
