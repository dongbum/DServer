#include "excel_conn.h"

ExcelConn::ExcelConn(void)
	: is_init_(false)
{

}

ExcelConn::~ExcelConn(void)
{
	
}

bool ExcelConn::Connect(char * filename)
{
	try
	{
		if (true == xls_.Load(filename))
		{
			is_init_ = true;
			return true;
		}
	}
	catch (...)
	{
		
	}

	is_init_ = false;
	return false;
}

size_t ExcelConn::GetTotalWorkSheetCount(void)
{
	if (false == is_init_)
		return false;

	return static_cast<size_t>(xls_.GetTotalWorkSheets());
}

template<typename T>
bool ExcelConn::LoadSheet(char * sheet_name, bool is_first_row_index /* = true */)
{
	if (false == is_init_)
		return false;

	ExcelFormat::BasicExcelWorksheet* worksheet = xls_.GetWorksheet(sheet_name);
	if (nullptr == worksheet)
		return false;

	int start_row = 0;
	if (is_first_row_index)
		start_row = 1;
		
	for (int k = start_row; k < worksheet->GetTotalRows(); ++k)
	{
		for (int j = 0; j < worksheet->GetTotalCols(); ++j)
		{
			ExcelFormat::BasicExcelCell* cell = worksheet->Cell(k, j);
			if (nullptr == cell)
				continue;

			switch (cell->Type())
			{
			case ExcelFormat::BasicExcelCell::INT:
				std::cout << "INT:" << cell->GetInteger() << std::endl;
				break;
			case ExcelFormat::BasicExcelCell::DOUBLE:
				std::cout << "DOUBLE:" << static_cast<int>(cell->GetDouble()) << std::endl;
				break;
			case ExcelFormat::BasicExcelCell::STRING:
				std::cout << "STRING:" << cell->GetString() << std::endl;
				break;
			case ExcelFormat::BasicExcelCell::WSTRING:
				std::cout << "WSTRING:" << cell->GetWString() << std::endl;
				break;
			case ExcelFormat::BasicExcelCell::UNDEFINED:
			case ExcelFormat::BasicExcelCell::FORMULA:
			default:
				break;
			}
		}
	}

	return true;
}
