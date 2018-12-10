#include "excel_conn.h"

ExcelConn::ExcelConn(void)
{
}

ExcelConn::~ExcelConn(void)
{
}

bool ExcelConn::Connect(char * filename)
{
	if (false == xls_.Load(filename))
		return false;

	return true;
}

bool ExcelConn::LoadSheet(char * sheet_name)
{
	

	return false;
}
