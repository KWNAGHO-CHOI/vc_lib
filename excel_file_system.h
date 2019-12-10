#pragma once

#include <xlnt/xlnt.hpp>
#include <xlnt/styles/font.hpp>
#include <xlnt/styles/style.hpp>
#include <xlnt/styles/fill.hpp>
#include <xlnt/styles/color.hpp>
#include <xlnt/utils/path.hpp>
#include <direct.h>
#include "vc_lib.h"

#define XLNT_BORDER_LIST_MAX		50
#define XLNT_FONT_LIST_MAX		50

#define ALIGMENT_CENTER		1
#define ALIGMENT_LEFT		2
#define ALIGMENT_RIGHT		3

typedef struct __excel_file_handle_type{
	char folder_name[_MAX_PATH];
	char folder_path[_MAX_PATH];
	char file_name[_MAX_PATH];
	char file_path[_MAX_PATH];
	int now_row;
	int list_number;
}EXCEL_FILE_HANDLE_TYPE;

ref class excel_file_system : public vc_lib
{
private:
	int now_column;
	int now_row;
	int draw_file_Header_flag;
public:
	excel_file_system();
	void backup_workbook(xlnt::workbook wb);
	void restore_workbook(xlnt::workbook &wb);
	char* get_folder_path(EXCEL_FILE_HANDLE_TYPE excel_file_handle);
	char* get_file_path(EXCEL_FILE_HANDLE_TYPE excel_file_handle);
	void enable_drw_file_header_flag();
	int get_drw_file_header_flag();
	void set_now_row(int now_row);
	int get_now_row();

	///////////////////////////////////////////////////////////////////////
	// 셀내용을 str_value(char * type)와 비교 후 결과를 return 한다. 
	// 결과 true: 일치, false: 불일치
	bool cell_Check_for_duplicates(xlnt::worksheet &ws, xlnt::column_t column, xlnt::row_t row, char *str_value);
	///////////////////////////////////////////////////////////////////////
	// 셀내용을 int_value(int type)와 비교 후 결과를 return 한다. 
	// 결과 true: 일치, false: 불일치
	bool cell_Check_for_duplicates(xlnt::worksheet &ws, xlnt::column_t column, xlnt::row_t row, int int_value);
	///////////////////////////////////////////////////////////////////////
	// 셀내용을 return (int type)한다. 
	int cell_read(xlnt::worksheet& ws, int& out_data, xlnt::column_t column, xlnt::row_t row);

	// merge 추가 버젼
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row, xlnt::font &set_font, char *str_value, int width, xlnt::alignment aligment, const std::string &hex_color, xlnt::border &set_border);
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row, xlnt::font &set_font, char *str_value, const std::string &hex_color, xlnt::border &set_border);
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row, xlnt::font &set_font, int int_value, int width, xlnt::alignment aligment, const std::string &hex_color, xlnt::border &set_border);
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row, xlnt::font &set_font, int int_value, const std::string &hex_color, xlnt::border &set_border);
	// 일반 버젼
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t cell_column, xlnt::row_t cell_row, xlnt::font &set_font, char *str_value, int width, xlnt::alignment aligment, const std::string &hex_color, xlnt::border &set_border);
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t cell_column, xlnt::row_t cell_row, xlnt::font &set_font, char *str_value, const std::string &hex_color, xlnt::border &set_border);
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t cell_column, xlnt::row_t cell_row, xlnt::font &set_font, int int_value, int width, xlnt::alignment aligment, const std::string &hex_color, xlnt::border &set_border);
	void set_cell_Value(xlnt::worksheet &ws, xlnt::column_t cell_column, xlnt::row_t cell_row, xlnt::font &set_font, int int_value, const std::string &hex_color, xlnt::border &set_border);

	void set_cell_fill_Color(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row,const std::string &hex_color);
	void set_cell_border_outside(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row);
	void set_cell_border(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row, xlnt::border &set_border);
	void set_cell_border(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row);
	void set_cell_merge(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row);
	void set_cell_unmerge(xlnt::worksheet &ws, xlnt::column_t start_column, xlnt::row_t start_row, xlnt::column_t end_column, xlnt::row_t end_row);
	void set_freeze_panes(xlnt::worksheet &ws, xlnt::column_t column, xlnt::row_t row);
	virtual ~excel_file_system();
};


