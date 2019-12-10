#include "excel_file_system.h"


char folder_pach[_MAX_PATH] = " ";
char file_pach[_MAX_PATH] = " ";

char file_path[_MAX_PATH] = " ";
xlnt::workbook wb_backup;

excel_file_system::excel_file_system()
{
}

excel_file_system::~excel_file_system()
{
}

void excel_file_system::backup_workbook(xlnt::workbook wb)
{
	wb_backup = wb;
}

void excel_file_system::restore_workbook(xlnt::workbook &wb)
{
	wb = wb_backup;
}

char* excel_file_system::get_folder_path(EXCEL_FILE_HANDLE_TYPE excel_file_handle)
{
	return excel_file_handle.folder_path;
}

char* excel_file_system::get_file_path(EXCEL_FILE_HANDLE_TYPE excel_file_handle)
{
	return excel_file_handle.file_path;
}

void excel_file_system::enable_drw_file_header_flag()
{
	this->draw_file_Header_flag = 1;
}

int excel_file_system::get_drw_file_header_flag()
{
	return this->draw_file_Header_flag;
}

void excel_file_system::set_now_row(int now_row)
{
	this->now_row = now_row;
}

int excel_file_system::get_now_row()
{
	return (this->now_row + 1);
}

void cell_clear(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row)
{

}

bool excel_file_system::cell_Check_for_duplicates(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	char *str_value)
{
	bool result = false;

	char read_value[100];
	To_Char(ws.cell(start_column, start_row).to_string(), read_value, 100);

	if (Data_Cmp(read_value, str_value,strlen(str_value)) == 0)
	{
		result = true;
	}

	return (result);
}

int excel_file_system::cell_read(xlnt::worksheet& ws, int &out_data, xlnt::column_t column,	xlnt::row_t row)
{
	out_data = To_int(ws.cell(column, row).to_string());

	return (1);
}

bool excel_file_system::cell_Check_for_duplicates(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	int int_value)
{
	bool result = false;

	char int_value_str[100];
	char read_value[100];

	sprintf_s(int_value_str, 100, "%d", int_value);
	To_Char(ws.cell(start_column, start_row).to_string(), read_value, 100);

	if (Data_Cmp(read_value, int_value_str, strlen(int_value_str)) == 0)
	{
		result = true;
	}

	return (result);
}


void excel_file_system::set_cell_Value(	// str_value 셀 폭 설정 용
	xlnt::worksheet &ws,
	xlnt::column_t cell_column,
	xlnt::row_t cell_row,
	xlnt::font &set_font,
	char *str_value,
	int width,
	xlnt::alignment aligment,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	ws.column_properties(cell_column).width = width;		// cell_column 넓이 설정
	ws.cell(cell_column, cell_row).font(set_font);			// 글자 설정
	ws.cell(cell_column, cell_row).value(ANSItoUTF8(str_value));		// 셀 내용 적용
	ws.cell(cell_column, cell_row).alignment(aligment);		// 글자 정렬 설정
	ws.cell(cell_column, cell_row).fill(xlnt::fill::solid(xlnt::rgb_color(hex_color)));	// 셀 배경 색 설정
	ws.cell(cell_column, cell_row).border(set_border);		// 셀 테두리 선 설정
}


void excel_file_system::set_cell_Value(	// str_value 셀 폭 설정 용 (merge_cells 기능 추가)
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	xlnt::font &set_font,
	char *str_value,
	int width,
	xlnt::alignment aligment,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	int duplicates_result = 0;
	if (cell_Check_for_duplicates(ws, start_column, start_row, end_column, end_row, str_value) == true)
	{
		duplicates_result = 1;
	}

	if ((start_column != end_column) || (start_row != end_row))
	{
		if (duplicates_result == 0)
		{
			set_cell_border_outside(ws, start_column, start_row, end_column, end_row);
		}
	}
	else
	{
		ws.cell(start_column, start_row).border(set_border);									// 셀 테두리 선 설정
	}

	ws.column_properties(start_column).width = width;		// cell_column 넓이 설정
	ws.cell(start_column, start_row).font(set_font);			// 글자 설정
	ws.cell(start_column, start_row).value(ANSItoUTF8(str_value));		// 셀 내용 적용
	ws.cell(start_column, start_row).alignment(aligment);		// 글자 정렬 설정
	set_cell_fill_Color(ws, start_column, start_row, end_column, end_row, hex_color);	// 셀영역 배경 색 설정
}

void excel_file_system::set_cell_Value(	// str_value 셀폭 등 제외 사용 편의 성을 위해 간소화 타입
	xlnt::worksheet &ws,
	xlnt::column_t cell_column,
	xlnt::row_t cell_row,
	xlnt::font &set_font,
	char *str_value,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	xlnt::alignment aligment_center;
	aligment_center.horizontal(xlnt::horizontal_alignment::center);
	aligment_center.vertical(xlnt::vertical_alignment::center);

	ws.cell(cell_column, cell_row).font(set_font);			// 글자 설정
	ws.cell(cell_column, cell_row).value(ANSItoUTF8(str_value));		// 셀 내용 적용
	ws.cell(cell_column, cell_row).alignment(aligment_center);		// 글자 셀 가운데 정렬 고정
	ws.cell(cell_column, cell_row).fill(xlnt::fill::solid(xlnt::rgb_color(hex_color)));	// 셀 배경 색 설정
	ws.cell(cell_column, cell_row).border(set_border);		// 셀 테두리 선 설정
}

void excel_file_system::set_cell_Value(	// str_value 셀폭 등 제외 사용 편의 성을 위해 간소화 타입 (merge_cells 기능 추가)
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	xlnt::font &set_font,
	char *str_value,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	xlnt::alignment aligment_center;
	aligment_center.horizontal(xlnt::horizontal_alignment::center);
	aligment_center.vertical(xlnt::vertical_alignment::center);

	int duplicates_result = 0;
	if (cell_Check_for_duplicates(ws, start_column, start_row, end_column, end_row, str_value) == true)
	{
		duplicates_result = 1;
	}

	if ((start_column != end_column) || (start_row != end_row))
	{
		if (duplicates_result == 0)
		{
			set_cell_border_outside(ws, start_column, start_row, end_column, end_row);
		}
	}
	else
	{
		ws.cell(start_column, start_row).border(set_border);									// 셀 테두리 선 설정
	}

	ws.cell(start_column, start_row).font(set_font);										// 글자 설정
	ws.cell(start_column, start_row).value(ANSItoUTF8(str_value));		// 셀 내용 적용
	ws.cell(start_column, start_row).alignment(aligment_center);							// 글자 셀 가운데 정렬 고정
	set_cell_fill_Color(ws, start_column, start_row, end_column, end_row, hex_color);	// 셀영역 배경 색 설정
}

void excel_file_system::set_cell_Value(// int_value 셀 폭 설정 용
	xlnt::worksheet &ws,
	xlnt::column_t cell_column,
	xlnt::row_t cell_row,
	xlnt::font &set_font,
	int int_value,
	int width,
	xlnt::alignment aligment,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	ws.column_properties(cell_column).width = width;		// cell_column 넓이 설정
	ws.cell(cell_column, cell_row).font(set_font);			// 글자 설정
	ws.cell(cell_column, cell_row).value(int_value);		// 셀 내용 적용
	ws.cell(cell_column, cell_row).alignment(aligment);		// 글자 정렬 설정
	ws.cell(cell_column, cell_row).fill(xlnt::fill::solid(xlnt::rgb_color(hex_color)));	// 셀 배경 색 설정
	ws.cell(cell_column, cell_row).border(set_border);		// 셀 테두리 선 설정
}

void excel_file_system::set_cell_Value(	// int_value 셀 폭 설정 용 (merge_cells 기능 추가)
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	xlnt::font &set_font,
	int int_value,
	int width,
	xlnt::alignment aligment,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	int duplicates_result = 0;
	if (cell_Check_for_duplicates(ws, start_column, start_row, end_column, end_row, int_value) == true)
	{
		duplicates_result = 1;
	}

	if ((start_column != end_column) || (start_row != end_row))
	{
		if (duplicates_result == 0)
		{
			set_cell_border_outside(ws, start_column, start_row, end_column, end_row);
		}
	}
	else
	{
		ws.cell(start_column, start_row).border(set_border);									// 셀 테두리 선 설정
	}

	ws.column_properties(start_column).width = width;		// cell_column 넓이 설정
	ws.cell(start_column, start_row).font(set_font);			// 글자 설정
	ws.cell(start_column, start_row).value(int_value);		// 셀 내용 적용
	ws.cell(start_column, start_row).alignment(aligment);		// 글자 정렬 설정
	set_cell_fill_Color(ws, start_column, start_row, end_column, end_row, hex_color);	// 셀영역 배경 색 설정
}

void excel_file_system::set_cell_Value(	// int_value 셀폭 등 제외 사용 편의 성을 위해 간소화 타입
	xlnt::worksheet &ws,
	xlnt::column_t cell_column,
	xlnt::row_t cell_row,
	xlnt::font &set_font,
	int int_value,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	xlnt::alignment aligment_center;
	aligment_center.horizontal(xlnt::horizontal_alignment::center);
	aligment_center.vertical(xlnt::vertical_alignment::center);

	ws.cell(cell_column, cell_row).font(set_font);					// 글자 설정
	ws.cell(cell_column, cell_row).value(int_value);				// 셀 내용 적용
	ws.cell(cell_column, cell_row).alignment(aligment_center);		// 글자 셀 가운데 정렬 고정
	ws.cell(cell_column, cell_row).fill(xlnt::fill::solid(xlnt::rgb_color(hex_color)));	// 셀 배경 색 설정
	ws.cell(cell_column, cell_row).border(set_border);		// 셀 테두리 선 설정
}

void excel_file_system::set_cell_Value(	// int_value 셀폭 등 제외 사용 편의 성을 위해 간소화 타입 (merge_cells 기능 추가)
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	xlnt::font &set_font,
	int int_value,
	const std::string &hex_color,
	xlnt::border &set_border)
{
	xlnt::alignment aligment_center;
	aligment_center.horizontal(xlnt::horizontal_alignment::center);
	aligment_center.vertical(xlnt::vertical_alignment::center);

	int duplicates_result = 0;
	if (cell_Check_for_duplicates(ws, start_column, start_row, end_column, end_row, int_value) == true)
	{
		duplicates_result = 1;
	}

	if ((start_column != end_column) || (start_row != end_row))
	{
		if (duplicates_result == 0)
		{
			set_cell_border_outside(ws, start_column, start_row, end_column, end_row);
		}
	}
	else
	{
		ws.cell(start_column, start_row).border(set_border);									// 셀 테두리 선 설정
	}

	ws.cell(start_column, start_row).font(set_font);										// 글자 설정
	ws.cell(start_column, start_row).value(int_value);		// 셀 내용 적용
	ws.cell(start_column, start_row).alignment(aligment_center);							// 글자 셀 가운데 정렬 고정
	set_cell_fill_Color(ws, start_column, start_row, end_column, end_row, hex_color);	// 셀영역 배경 색 설정
}

void excel_file_system::set_cell_fill_Color(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	const std::string &hex_color)
{
	for (auto cnt_row = start_row; cnt_row <= end_row; cnt_row++)
	{
		for (auto cnt_column = start_column; cnt_column <= end_column; cnt_column++)
		{
			ws.cell(cnt_column, cnt_row).fill(xlnt::fill::solid(xlnt::rgb_color(hex_color)));	// 셀 배경 색 설정
		}
	}
}

void excel_file_system::set_cell_border_outside(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row)
{
	xlnt::border::border_property border_property;
	xlnt::border set_Start;
	xlnt::border set_middle;
	xlnt::border set_end;

	border_property.style(xlnt::border_style::thin);
	set_Start.side(xlnt::border_side::start, border_property); // left       [
//	set_Start.side(xlnt::border_side::end, border_property); // right
	set_Start.side(xlnt::border_side::top, border_property); // top
	set_Start.side(xlnt::border_side::bottom, border_property); // bottom

//	set_middle.side(xlnt::border_side::start, border_property); // left      =
//	set_middle.side(xlnt::border_side::end, border_property); // right
	set_middle.side(xlnt::border_side::top, border_property); // top
	set_middle.side(xlnt::border_side::bottom, border_property); // bottom

//	set_end.side(xlnt::border_side::start, border_property); // left         ]
	set_end.side(xlnt::border_side::end, border_property); // right
	set_end.side(xlnt::border_side::top, border_property); // top
	set_end.side(xlnt::border_side::bottom, border_property); // bottom

	for (auto cnt_row = start_row; cnt_row <= end_row; cnt_row++)
	{
		for (auto cnt_column = start_column; cnt_column <= end_column; cnt_column++)
		{
			if (cnt_column == start_column)
			{
				ws.cell(cnt_column, cnt_row).border(set_Start);	// 영역내 모든 외각선 활성화 [
			}
			else if (cnt_column == end_column)
			{
				ws.cell(cnt_column, cnt_row).border(set_end);	// 영역내 모든 외각선 활성화 ]
			}
			else
			{
				ws.cell(cnt_column, cnt_row).border(set_middle);	// 영역내 모든 외각선 활성화  =
			}
		}
	}
}

void excel_file_system::set_cell_border(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row,
	xlnt::border &set_border)
{
	for (auto cnt_row = start_row; cnt_row <= end_row; cnt_row++)
	{
		for (auto cnt_column = start_column; cnt_column <= end_column; cnt_column++)
		{
			ws.cell(cnt_column, cnt_row).border(set_border);	// 영역내 모든 외각선 활성화
		}
	}
	ws.merge_cells(xlnt::range_reference(start_column, start_row, end_column, end_row));	//	셀병합
}

void excel_file_system::set_cell_border(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row)
{
	xlnt::border border_No_side;	//	외각선 없는 타입

	for (auto cnt_row = start_row; cnt_row <= end_row; cnt_row++)
	{
		for (auto cnt_column = start_column; cnt_column <= end_column; cnt_column++)
		{
			ws.cell(cnt_column, cnt_row).border(border_No_side);	// 영역내 모든 외각선 활성화
		}
	}
	ws.merge_cells(xlnt::range_reference(start_column, start_row, end_column, end_row));	//	셀병합
}


void excel_file_system::set_cell_merge(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row)
{
	ws.merge_cells(xlnt::range_reference(start_column, start_row, end_column, end_row));	//	셀병합

}

void excel_file_system::set_cell_unmerge(
	xlnt::worksheet &ws,
	xlnt::column_t start_column,
	xlnt::row_t start_row,
	xlnt::column_t end_column,
	xlnt::row_t end_row)
{
	ws.unmerge_cells(xlnt::range_reference(start_column, start_row, end_column, end_row));	//	셀병합 해제

}


void excel_file_system::set_freeze_panes(
	xlnt::worksheet &ws,
	xlnt::column_t column,
	xlnt::row_t row)
{
	ws.freeze_panes(xlnt::cell_reference(column, row));		//	틀고정
}
