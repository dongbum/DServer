#pragma once

#include "excelformat/excelformat.h"

class ExcelConn
{
public:
	ExcelConn(void);
	virtual ~ExcelConn(void);

	bool Connect(char* file_name);
	size_t GetTotalWorkSheetCount(void);

	bool LoadSheet(char* sheet_name, OUT std::map<int, std::vector<std::string>>& data_container, bool is_first_row_index = true);

private:
	ExcelFormat::BasicExcel xls_;
	bool is_init_;
};
