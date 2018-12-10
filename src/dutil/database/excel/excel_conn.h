#pragma once

#include "excelformat/excelformat.h"

class ExcelConn
{
public:
	ExcelConn(void);
	virtual ~ExcelConn(void);

	bool Connect(char* file_name);
	bool LoadSheet(char* sheet_name);

private:
	ExcelFormat::BasicExcel xls_;

};
