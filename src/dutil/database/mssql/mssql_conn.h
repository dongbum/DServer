#pragma once

// SQLBindParameter에 필요가 타입 정보
typedef struct DESC_PARAM_STRUCT
{
	SQLSMALLINT					cdata_type;
	SQLSMALLINT					sql_data_type;
	SQLULEN						param_size;
	SQLSMALLINT					decimal_digits;
	SQLSMALLINT					nullable;
	DESC_PARAM_STRUCT(void)
		: cdata_type(0), sql_data_type(0), param_size(0), decimal_digits(0), nullable(0)
	{}
} DESC_PARAM;

// DESC_PARAM 관리 구조체
typedef struct  QUERY_DESC_PARAM_STRUCT
{
	bool						is_no_data;		// SQLBindParameter 존재여부 체크
	std::vector<DESC_PARAM>		desc_param_vec;	// SQLBindParameter Type 정보
	QUERY_DESC_PARAM_STRUCT(void)
		: is_no_data(false) {}
} QUERY_DESC_PARAM;

// SQLBindCol에 필요가 정보
typedef struct COL_ATTR_STRUCT
{
	bool						is_cached;
	SQLSMALLINT					desc_type;
	SQLLEN						desc_len;
	COL_ATTR_STRUCT(void)
		: is_cached(false), desc_type(0), desc_len(0) {}
} COL_ATTR;

typedef struct QUERY_COL_ATTR_STRUCT
{
	bool						is_no_data;		// SQLBindCol 존재여부 체크
	std::vector<COL_ATTR>		col_attr_vec;	// SQLBindCol Type 정보
	QUERY_COL_ATTR_STRUCT(void)
		: is_no_data(false) {}
} QUERY_COL_ATTR;

class MSSQLConn
{
public:
	typedef std::vector<QUERY_DESC_PARAM>	QueryDescParamVec;
	typedef std::vector<QUERY_COL_ATTR>		QueryColAttrVec;

	explicit MSSQLConn(int32_t& total_query);
	virtual ~MSSQLConn(void);

	bool Connect(TCHAR* connection_string);
	void Disconnect(void);

	bool PrepareQuery(uint16_t query_type, TCHAR* query_info);
	bool BindParamInput(void* value);
	bool BindParamOutput(void* value);
	bool BindCol(void* value);

	bool Execute(void);

	bool IsConnDead(void);

private:
	bool InitEnvHandle(void);
	bool InitConnectHandle(void);
	bool InitStmtHandle(void);

	void ClearStmt(void);
	void SetDescribeParam(void);	// SQLBindParameter 타입 셋팅
	void SetColAttr(void);			// SQLBindCol 타입 셋팅

	SQLSMALLINT		GetCDataType(SQLSMALLINT sql_data_type);		// C Data Type 가져오기
	TCHAR*			GetDBEErrorMessage(const SQLSMALLINT handle_type, const SQLHENV & statement, TCHAR message[]);

private:
	SQLHENV			henv_;
	SQLHDBC			hdbc_;
	SQLHSTMT		hstmt_;

	uint16_t		query_num_;
	int16_t			param_num_;		// Bind Parameter Number (BindParameter함수 호출될 때마다 1증가)
	int16_t			col_num_;		//  Bind Col Number (BindCol함수 호출될 때마다 1증가)
	SQLINTEGER		fetched_rows_;	// Row 카운터

	QueryDescParamVec	query_desc_param_vec_;	// SQLBindParameter Type 관리용 (std::vector 사용)
	QueryColAttrVec		query_col_attr_vec_;	// SQLBindCol Type 관리용 (std::vector 사용)

};
