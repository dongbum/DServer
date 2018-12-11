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

bool ExcelConn::LoadSheet(char* sheet_name, OUT std::map<int, std::vector<std::string>>& data_container, bool is_first_row_index /* = true */)
{
	if (false == is_init_)
		return false;
	
	ExcelFormat::BasicExcelWorksheet* worksheet = xls_.GetWorksheet(sheet_name);
	if (nullptr == worksheet)
		return false;

	int start_row = 0;
	if (is_first_row_index)
		start_row = 1;
	
	data_container.clear();

	int index = 0;
	for (int k = start_row; k < worksheet->GetTotalRows(); ++k)
	{
		std::vector<std::string> row_data;

		for (int j = 0; j < worksheet->GetTotalCols(); ++j)
		{
			ExcelFormat::BasicExcelCell* cell = worksheet->Cell(k, j);
			if (nullptr == cell)
				continue;

			switch (cell->Type())
			{
			case ExcelFormat::BasicExcelCell::INT:
				row_data.push_back(std::to_string(cell->GetInteger()));
				break;
			case ExcelFormat::BasicExcelCell::DOUBLE:
				row_data.push_back(std::to_string(cell->GetDouble()));
				break;
			case ExcelFormat::BasicExcelCell::STRING:
				row_data.push_back(cell->GetString());
				break;
			case ExcelFormat::BasicExcelCell::WSTRING:
			case ExcelFormat::BasicExcelCell::UNDEFINED:
			case ExcelFormat::BasicExcelCell::FORMULA:
			default:
				{
					data_container.clear();
					return false;
				}
				break;
			}
		}

		data_container.insert(std::map<int, std::vector<std::string>>::value_type(index, row_data));

		++index;
	}

	return true;
}
