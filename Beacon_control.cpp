#include "Beacon_control.h"



UART_DATA_QUEUE Uart1;

CONTROL_VARIABLE BLE_Scanner = { 0 };

SERIAL_DECODER_TYPE serialPort1_decoder;

SCAN_LIST_QUEUE	Scan_List_Q[BLE_SCANNER_LIST_MAX] = { 0 };
BLE_SCAN_LIST BLE_Scanner_list[BLE_SCANNER_LIST_MAX] = { 0 };
BLE_SCAN_LIST BLE_Scanner_list_fixing[BLE_SCANNER_LIST_MAX] = { 0 };


BLE_SCAN_LIST BLE_Scanner_list_Complete[BLE_SCANNER_LIST_MAX] = { 0 };
BLE_SCAN_LIST BLE_Scanner_list_Revocation[BLE_SCANNER_LIST_MAX] = { 0 };
BLE_SCAN_LIST BLE_Scanner_list_Control_All = { 0 };
BLE_SCAN_LIST *BLE_Scanner_list_Control_All_Complete = 0;
BLE_SCAN_LIST BLE_Scanner_list_Control_Dummy = { 0 };

SCAN_DATA	Check_Data = { 0 };

SCAN_DATA	BLE_ALL_Auto_Control_Data = { 0 };
SCAN_DATA	MAC_Address_Setting_Data = { 0 };
SCAN_DATA	MAC_Address_Setting_Data_Revocation = { 0 };

int BLE_MAC_Address_Setting_Auto_Process_Delay = 0;
int BLE_MAC_Address_Setting_Auto_Process_flag = 0;

int New_Mac_Number = 1;

#define	MAC_ADDRESS_SET_NOW		0
#define	MAC_ADDRESS_SET_NEW		1
#define	MAC_ADDRESS_SET_BUFF_MAX		2
unsigned char Mac_Address_Set_Buff[MAC_ADDRESS_SET_BUFF_MAX][6] = { 0 };

int BLE_Scan_List_Cnt_Group[4] = { 0 };
int BLE_Scan_List_Cnt_Group_Before[4] = { 0 };

unsigned char BLE_Scan_List[800][10] = { 0 };

unsigned char Copy_Buff1[20] = { 0 };
unsigned char Copy_Buff_CMD_0[100] = { 0 };
unsigned char Copy_Buff_CMD[100] = { 0 };
unsigned char Copy_Buff_RES[100] = { 0 };
unsigned char BLE_CMD_TxRes_Check_Buff[100] = { 0 };
unsigned char BLE_CMD_TxRes_Error_Check_Buff[100] = { 0 };

unsigned char BLE_Remote_control_Mac_addr[6] = { 0 };

unsigned char BLE_Scan_List_NORMAL[200][10] = { 0 };
int BLE_Scan_List_NORMAL_Cnt_FI = 0;
int BLE_Scan_List_NORMAL_Cnt = 0;
int BLE_Scan_List_NORMAL_Cnt_Before = 0;

unsigned char BLE_Scan_List_CONITE[200][10] = { 0 };
int BLE_Scan_List_CONITE_Cnt_FI = 0;
int BLE_Scan_List_CONITE_Cnt = 0;
int BLE_Scan_List_CONITE_Cnt_Before = 0;

unsigned char BLE_Scan_List_MANUFACTURE[200][10] = { 0 };
int BLE_Scan_List_MANUFACTURE_Cnt_FI = 0;
int BLE_Scan_List_MANUFACTURE_Cnt = 0;
int BLE_Scan_List_MANUFACTURE_Cnt_Before = 0;

unsigned char BLE_Scan_List_OTHER[200][10] = { 0 };
int BLE_Scan_List_OTHER_Cnt_FI = 0;
int BLE_Scan_List_OTHER_Cnt = 0;
int BLE_Scan_List_OTHER_Cnt_Before = 0;

unsigned char BLE_Scan_List_Temp_Buff[20] = { 0 };
int BLE_Scan_List_Temp_Buff_Cnt = 0;

int TimerCnt = 0;
int RxCnt = 0;
int WriteCnt = 0;
int dataCnt = 0;
int Item_Num = 0;
int BLE_Scan_List_Cnt = 0;
int BLE_List_Max_FI = 0;
int BLE_Scan_List_Cnt_Before = 0;
int BLE_Scan_List_renewal = 0;
int BLE_Remote_Control_Target_Index = 0;

char BLE_Remote_Contorl_Auto_CMD = 0;
int BLE_Remote_Contorl_Auto_Enable = 0;
int BLE_Remote_Contorl_Auto_Delay = 0;
int BLE_Remote_Contorl_Auto_Delay_cnt = 0;
int BLE_Remote_Control_Target_Index_Auto = 0;
int BLE_Remote_Control_Target_Index_Auto_End = 0;

int BLE_CMD_Enable = 0;
int BLE_CMD_Now = 0;
int BLE_CMD_TxSeq = 0;
int BLE_CMD_Res_Length = 0;
int BLE_CMD_Res_Check_Seq = 0;

int BLE_Data_RxSeq = 0;
int BLE_CMD_RxSeq = 0;
int BLE_Manufacture_Report_RxSeq = 0;

int BLE_CMD_RxDataCopy_Cnt = 0;
int BLE_RES_RxDataCopy_Cnt = 0;

int BLE_CMD_Power_ALL_OFF = 0;
int BLE_CMD_LED_ALL_ON = 0;
int BLE_CMD_LED_ALL_OFF = 0;

int Uart_Req_Time_Out = 0;
int Uart_rx_Time_Out = 0;
int Uart_rx_Time_Out_Cnt = 0;

int BLE_Data_Type = BLE_SCAN_LIST_OFF_SET_NORMAL;
int BLE_Scan_List_Cnt_Group_NORMAL = 0;
int BLE_Scan_List_Cnt_Group_NORMAL_Before = 0;
int BLE_Scan_List_Cnt_Group_CONITE = 0;
int BLE_Scan_List_Cnt_Group_CONITE_Before = 0;
int BLE_Scan_List_Cnt_Group_MANUFACTURE = 0;
int BLE_Scan_List_Cnt_Group_MANUFACTURE_Before = 0;
int BLE_Scan_List_Cnt_Group_OTHER = 0;
int BLE_Scan_List_Cnt_Group_OTHER_Before = 0;

int Scanner_Program_mode = 0;
int Scanner_Program_Start_init = 0;

int BLE_ALL_Auto_Process_Delay = 0;
int BLE_ALL_Auto_Enable_flag = 0;
int BLE_ALL_Auto_Seq = 0;
int BLE_ALL_Auto_CMD = 0;

int BLE_Scan_Hardware_Test_View_init_flag = 0;

xlnt::font normal_font;
xlnt::font title_font;
xlnt::font List_subtitle_font;
xlnt::font red_Color_font;
xlnt::font blue_Color_font;
xlnt::font logo_font;

xlnt::alignment aligment_center;
xlnt::alignment aligment_left;
xlnt::alignment aligment_right;

//	셀 테두리 설정 용
xlnt::border::border_property border_property;
xlnt::border border_outside;
xlnt::border border_No_side;
xlnt::border border_outside_thick;

//	excel file handle
enum {
	 EXCEL_FILE_HW_TEST_REPORT = 0	//	Hardware_Test_Report
	,EXCEL_FILE_MAC_ALLOC_REPORT	//	MAC_Address_Allocation_Report
	,EXCEL_FILE_LIST_MAX
};

EXCEL_FILE_HANDLE_TYPE excel_file_handle_list[EXCEL_FILE_LIST_MAX] = {0};

void Beacon_control::excel_file_handle_setting(EXCEL_FILE_HANDLE_TYPE &excel_file_handle)
{
	//	폴더 생성 및 파일 경로 와 이름 설정
	sprintf_s(excel_file_handle.folder_path, _MAX_PATH, ".\\%s", excel_file_handle.folder_name);
	sprintf_s(excel_file_handle.file_path, _MAX_PATH, "%s\\%s", excel_file_handle.folder_path, excel_file_handle.file_name);
	excel_file_handle.now_row = 1;


	mkdir(excel_file_handle.folder_path);
}

void Beacon_control::excel_file_Constructor()
{
	//파일에 사용할 각 셀의 색, 폰트, 테두리를 미리 설정 한다.
	//	글자 속성 설정

	normal_font.bold(true);
	normal_font.size(12);
	normal_font.color(xlnt::color::black());

	title_font.bold(true);
	title_font.size(24);
	title_font.color(xlnt::rgb_color(TITLE_FONT_COLOR));

	List_subtitle_font.bold(true);
	List_subtitle_font.size(12);
	List_subtitle_font.color(xlnt::rgb_color(TITLE_FONT_COLOR));

	red_Color_font.bold(true);
	red_Color_font.size(12);
	red_Color_font.color(xlnt::rgb_color("00ff0000"));

	blue_Color_font.bold(true);
	blue_Color_font.size(12);
	blue_Color_font.color(xlnt::rgb_color("000000ff"));

	logo_font.bold(true);
	logo_font.size(12);
	logo_font.color(xlnt::rgb_color("00ffffff"));

	//	셀 내부 글자 정렬 속성 설정
	aligment_center.horizontal(xlnt::horizontal_alignment::center);
	aligment_center.vertical(xlnt::vertical_alignment::center);

	aligment_left.horizontal(xlnt::horizontal_alignment::left);
	aligment_left.vertical(xlnt::vertical_alignment::center);

	aligment_right.horizontal(xlnt::horizontal_alignment::right);
	aligment_right.vertical(xlnt::vertical_alignment::center);

	//	셀 테두리 설정
	border_property.style(xlnt::border_style::thin);
	border_outside.side(xlnt::border_side::start, border_property); // left
	border_outside.side(xlnt::border_side::end, border_property); // right
	border_outside.side(xlnt::border_side::top, border_property); // top
	border_outside.side(xlnt::border_side::bottom, border_property); // bottom

	border_property.style(xlnt::border_style::thick);
	border_outside_thick.side(xlnt::border_side::start, border_property); // left
	border_outside_thick.side(xlnt::border_side::end, border_property); // right
	border_outside_thick.side(xlnt::border_side::top, border_property); // top
	border_outside_thick.side(xlnt::border_side::bottom, border_property); // bottom


	sprintf_s(excel_file_handle_list[EXCEL_FILE_HW_TEST_REPORT].folder_name, _MAX_PATH, "1차 생산 제품 보고서");
	sprintf_s(excel_file_handle_list[EXCEL_FILE_HW_TEST_REPORT].file_name, _MAX_PATH, "1차 %s년%s월%s일.xlsx", date_Read("yyyy"), date_Read("MM"), date_Read("dd"));

	sprintf_s(excel_file_handle_list[EXCEL_FILE_MAC_ALLOC_REPORT].folder_name, _MAX_PATH, "2차 MAC 주소 할당 보고서");
	sprintf_s(excel_file_handle_list[EXCEL_FILE_MAC_ALLOC_REPORT].file_name, _MAX_PATH, "2차 %s년%s월%s일.xlsx", date_Read("yyyy"), date_Read("MM"), date_Read("dd"));

	excel_file_handle_setting(excel_file_handle_list[EXCEL_FILE_HW_TEST_REPORT]);
	excel_file_handle_setting(excel_file_handle_list[EXCEL_FILE_MAC_ALLOC_REPORT]);
}

void Beacon_control::excel_file_open_and_load(EXCEL_FILE_HANDLE_TYPE &excel_file_handle, xlnt::workbook &wb, xlnt::worksheet &ws, std::string &filename)
{
	char* file_path = excel_file_handle.file_path;
	filename = ANSItoUTF8(file_path);

	//	기록 준비 및 worksheet 활성화 

	FILE* pFile = NULL;
	pFile = std::fopen(file_path, "r");	//	1. 일단 파일 존재 유무를 확인 하기 위해 읽기 모드로 파일을 오픈한다.

	if (pFile != NULL)
	{
		// 2. 파일이 존재 하면 다른 프로그램에서 사용중인지 확인 하기 위해 "a" 추가 모드로 다시 열어서 오류가 반환 되는지 확인 한다.
		// 참고 사항 : "a" 추가 모드로 열었더니 제어 우선권이 프로그램으로 넘어와서 다른 프로그램에서 엑셀 파일을 열었어도 오류 없이 쓰기가 가능하다.
		//             단지 상대 엑셀 프로그램에서 작성 후 저장시 권한 없음으로 다름이름 저장을 해야 하며 현 프로그램 "BeaconScanner.exe" 이 종료 할때 까지 파일 삭제가 안된다.(파일 사용중으로 삭제 안됨)
		pFile = std::fopen(file_path, "a");

		// xlnt 프로그램 시 주의 사항 wb.save 한 뒤에는 반드시 다시 wb.load 를 하여야 그다음 내용이 읽혀져서 동기화 가된다 
		// wb.load 를 하지 않을시 기존 데이터를 잃어 버린다.
		// 즉 모든 기록을 세분화 하여 처리 하고 저장 후 새로운 내용 기록 시 wb.load 를 반듯이 해줘야 이어서 쓰기가 가능하다.
		// 반복 문을 써서 기록 해도 한계가 있다. 한번에 60줄 이상 처리 시 Error 처리됨.
		wb.load(filename);
	}
	ws = wb.active_sheet();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 기존 기록된 파일일 경우 이어서 쓸지점을 검색하는 함수
void Beacon_control::excel_now_row_Search(xlnt::worksheet& ws, EXCEL_FILE_HANDLE_TYPE& excel_file_handle, xlnt::column_t column, char * title_Signature)
{
	int end_row_cnt = 1;
	for (int row_cnt = 1; row_cnt < 100; row_cnt++)
	{
		if (excel.cell_Check_for_duplicates(ws, column, row_cnt, title_Signature) == true)
		{
			end_row_cnt = row_cnt + 1;
		}
	}

	for (; end_row_cnt < 10000; end_row_cnt++)
	{
		int read_data_now = 0;
		int read_data_next = 0;
		excel.cell_read(ws, read_data_now, column, end_row_cnt);
		excel.cell_read(ws, read_data_next, column, end_row_cnt + 1);

		if ((read_data_now + 1) != read_data_next)
		{
			excel_file_handle.now_row = end_row_cnt + 1;
			excel_file_handle.list_number = read_data_now + 1;
			break;
		}
	}
}

void Beacon_control::excel_Hardware_Test_Report(SCAN_DATA outlist_data, EXCEL_FILE_HANDLE_TYPE& excel_file_handle)
{
	//	기록 준비 및 worksheet 활성화 
	std::string filename;
	xlnt::workbook wb;
	xlnt::worksheet ws;
	excel_file_open_and_load(excel_file_handle, wb, ws, filename);
	//	파일 내용 중 보고서 부분 완성
	excel_HW_Test_Report_Header_write(ws, wb, excel_file_handle);
	//	파일 내용 중 리스트 부분 완성
	excel_HW_Test_Report_list_write(ws, wb, outlist_data, excel_file_handle);

	wb.save(filename);
}

void Beacon_control::excel_HW_Test_Report_Header_write(xlnt::worksheet &ws, xlnt::workbook &wb, EXCEL_FILE_HANDLE_TYPE& excel_file_handle)
{
	//	보고서 부분이 작성 되었는지 확인
	if (excel.cell_Check_for_duplicates(ws, 2, 1, "        1차 생산 제품 검사 보고서") == false)
	{
		char temp[_MAX_PATH];
		int row_cnt = 1;	//	엑셀 파일의 row 번호는 1부터 시작  (0 으로 하면 오류처리 됨)

		ws.title(ANSItoUTF8("하드웨어 생산 보고서"));	//	Tab title 설정

		//	틀고정 설정
		excel.set_freeze_panes(ws, 2, 11);		//	틀고정
		//	머릿글 부분 흰 바탕 필요 영역 색 지정
		excel.set_cell_fill_Color(ws, 2, 2, 6, 9, NORMAL_BG_COLOR);
		excel.set_cell_Value(ws, 1, row_cnt, title_font, "", 1, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	좌 경계 라인 폭 설정
		excel.set_cell_Value(ws, 7, row_cnt, title_font, "", 1, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	우 경계 라인 폭 설정

		// 제목
		excel.set_cell_fill_Color(ws, 2, row_cnt, 6, row_cnt, TITLE_BG_COLOR);
		excel.set_cell_Value(ws, 2, row_cnt, title_font, "        1차 생산 제품 검사 보고서", 5, aligment_left, TITLE_BG_COLOR, border_No_side);	//	제목

		row_cnt += 2;	//	<< 1칸 띄우기 >>
		// 작성일
		sprintf_s(temp, _MAX_PATH, "작성일 : %s년%s월%s일", date_Read("yyyy"), date_Read("MM"), date_Read("dd"));
		excel.set_cell_Value(ws, 2, row_cnt, normal_font, temp, 5, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	작성일

		row_cnt += 2;	//	<< 1칸 띄우기 >>
		// 1. 결과 보고 ( 소 제목 및 분류 )
		excel.set_cell_Value(ws, 2, row_cnt, normal_font, "1. 결과 보고", 5, aligment_left, NORMAL_BG_COLOR, border_No_side);		//	소 제목
		row_cnt++;	//	<< 다음줄 선택 >>
		excel.set_cell_Value(ws, 2, row_cnt, 3, row_cnt, List_subtitle_font, "      검사 진행 제품 수량", 5, aligment_left, TITLE_BG_COLOR, border_outside);	//	정상제품
		excel.set_cell_Value(ws, 4, row_cnt, 6, row_cnt, normal_font, ANSItoUTF8("                             1"), 8, aligment_left, NORMAL_BG_COLOR, border_outside);	//	정상제품 수량
		row_cnt++;	//	<< 다음줄 선택 >>

		excel.set_cell_Value(ws, 2, row_cnt, 3, row_cnt, List_subtitle_font, "      정상 판별 제품 수량", 5, aligment_left, TITLE_BG_COLOR, border_outside);	//	불량 제품
		excel.set_cell_Value(ws, 4, row_cnt, 6, row_cnt, normal_font, ANSItoUTF8("                             1"), 8, aligment_left, NORMAL_BG_COLOR, border_outside);	//	불량제품 수량

		row_cnt += 2;	//	<< 1칸 띄우기 >>
		// 2. 검사 비콘 리스트 제목 및 분류
		excel.set_cell_Value(ws, 2, row_cnt, normal_font, "2. 검사 비콘 리스트", 5, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	소 제목
		row_cnt++;	//	<< 다음줄 선택 >>
		excel.set_cell_Value(ws, 2, row_cnt, List_subtitle_font, "순서", 5, aligment_center, TITLE_BG_COLOR, border_outside);	//	순번
		excel.set_cell_Value(ws, 3, row_cnt, List_subtitle_font, "MAC 주소", 20, aligment_center, TITLE_BG_COLOR, border_outside);	//	맥주소
		excel.set_cell_Value(ws, 4, row_cnt, List_subtitle_font, "수신감도", 8, aligment_center, TITLE_BG_COLOR, border_outside);	//	수신감도
		excel.set_cell_Value(ws, 5, row_cnt, List_subtitle_font, "전원 전압", 15, aligment_center, TITLE_BG_COLOR, border_outside);	//	전원 전압
		excel.set_cell_Value(ws, 6, row_cnt, List_subtitle_font, "결과 상태", 15, aligment_center, TITLE_BG_COLOR, border_outside);	//	검사 결과

		excel_file_handle.now_row = row_cnt + 1;
		excel_file_handle.list_number = 1;
	}
	else
	{
		excel_now_row_Search(ws, excel_file_handle, 2, "순서");
	}

}

void Beacon_control::excel_HW_Test_Report_list_write(xlnt::worksheet &ws, xlnt::workbook &wb, SCAN_DATA outlist_data, EXCEL_FILE_HANDLE_TYPE& excel_file_handle)
{
	char temp[_MAX_PATH];

	int now_row = excel_file_handle.now_row;

	//	이하 내용 완성 ( 실 검사 리스트 작성 )
	int testProgress_Quantity = excel_file_handle.list_number;
	int Complete_Quantity_now = 0;

	excel.set_cell_Value(ws, 2, now_row, normal_font, excel_file_handle.list_number, NORMAL_BG_COLOR, border_outside);	//	순번

	sprintf_s(temp, _MAX_PATH, "%02X:%02X:%02X:%02X:%02X:%02X" 
		, outlist_data.mac.d8bit[5]
		, outlist_data.mac.d8bit[4]
		, outlist_data.mac.d8bit[3]
		, outlist_data.mac.d8bit[2]
		, outlist_data.mac.d8bit[1]
		, outlist_data.mac.d8bit[0]);
	excel.set_cell_Value(ws, 3, now_row, normal_font, temp, NORMAL_BG_COLOR, border_outside);			//	맥주소

	sprintf_s(temp, _MAX_PATH, "%d dbm"
		, (signed char)outlist_data.sub_data[1]);
	excel.set_cell_Value(ws, 4, now_row, normal_font, temp, NORMAL_BG_COLOR, border_outside);		//	수신감도

	sprintf_s(temp, _MAX_PATH, "%.1f V"
		, (float)outlist_data.sub_data[0]/ 10.0f);
	excel.set_cell_Value(ws, 5, now_row, normal_font, temp, NORMAL_BG_COLOR, border_outside);			//	전원 전압

	excel.set_cell_Value(ws, 6, now_row, blue_Color_font, "정상", NORMAL_BG_COLOR, border_outside);	//	검사 결과

	// 1. 결과 보고 ( 내용 )
	
	sprintf_s(temp, _MAX_PATH, "                         %5d", testProgress_Quantity);
	excel.set_cell_Value(ws, 4, 6, 6, 6, normal_font, ANSItoUTF8(temp), 8, aligment_left, NORMAL_BG_COLOR, border_outside);	//	검사 진행 제품 수량

	Complete_Quantity_now = excel.cell_Word_search_and_count(ws, 6, now_row - excel_file_handle.list_number, 6, now_row, "정상");

	sprintf_s(temp, _MAX_PATH, "                         %5d", Complete_Quantity_now);
	excel.set_cell_Value(ws, 4, 7, 6, 7, normal_font, ANSItoUTF8(temp), 8, aligment_left, NORMAL_BG_COLOR, border_outside);	//	정상 판별 제품 수량

	excel_file_handle.now_row = now_row + 1;

}

void Beacon_control::excel_MAC_Address_Allocation_Report(SCAN_DATA ListBefore, SCAN_DATA ListAfter, EXCEL_FILE_HANDLE_TYPE& excel_file_handle)
{
	//	기록 준비 및 worksheet 활성화 
	std::string filename;
	xlnt::workbook wb;
	xlnt::worksheet ws;
	excel_file_open_and_load(excel_file_handle, wb, ws, filename);

	//	파일 내용 중 보고서 부분 완성
	excel_MAC_Address_Allocation_Report_Header_write(ws, wb, excel_file_handle);
	//	파일 내용 중 리스트 부분 완성
	excel_MAC_Address_Allocation_Report_list_write(ws, wb, ListBefore, ListAfter, excel_file_handle);

	wb.save(filename);
}

void Beacon_control::excel_MAC_Address_Allocation_Report_Header_write(xlnt::worksheet& ws, xlnt::workbook& wb, EXCEL_FILE_HANDLE_TYPE& excel_file_handle)
{

	if (excel.cell_Check_for_duplicates(ws, 2, 1, "        2차 MAC 주소 할당 보고서") == false)
	{
		char temp[_MAX_PATH];
		int row_cnt = 1;	//	엑셀 파일의 row 번호는 1부터 시작  (0 으로 하면 오류처리 됨)

		ws.title(ANSItoUTF8("MAC 주소 할당 보고서"));	//	Tab title 설정
		//	틀고정 설정
		excel.set_freeze_panes(ws, 2, 11);		//	2, 11 = 셀"B11"위치 틀고정
		//	머릿글 부분 흰 바탕 필요 영역 색 지정
		excel.set_cell_fill_Color(ws, 2, 2, 6, 9, NORMAL_BG_COLOR);
		excel.set_cell_Value(ws, 1, row_cnt, title_font, "", 1, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	좌 경계 라인 폭 설정
		excel.set_cell_Value(ws, 7, row_cnt, title_font, "", 1, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	우 경계 라인 폭 설정

		// 제목
		excel.set_cell_fill_Color(ws, 2, row_cnt, 6, row_cnt, TITLE_BG_COLOR);
		excel.set_cell_Value(ws, 2, row_cnt, title_font, "        2차 MAC 주소 할당 보고서", 5, aligment_left, TITLE_BG_COLOR, border_No_side);	//	제목

		row_cnt += 2;	//	<< 1칸 띄우기 >>
		// 작성일
		sprintf_s(temp, _MAX_PATH, "작성일 : %s년%s월%s일", date_Read("yyyy"), date_Read("MM"), date_Read("dd"));
		excel.set_cell_Value(ws, 2, row_cnt, normal_font, temp, 5, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	작성일

		row_cnt += 2;	//	<< 1칸 띄우기 >>
		// 1. 결과 보고 ( 소 제목 및 분류 )
		excel.set_cell_Value(ws, 2, row_cnt, normal_font, "1. 결과 보고", 5, aligment_left, NORMAL_BG_COLOR, border_No_side);		//	소 제목
		row_cnt++;	//	<< 다음줄 선택 >>
		excel.set_cell_Value(ws, 2, row_cnt, 3, row_cnt, List_subtitle_font, "      MAC 주소 설정 제품 수량", 5, aligment_left, TITLE_BG_COLOR, border_outside);	//	MAC 주소 설정 제품 수량
		excel.set_cell_Value(ws, 4, row_cnt, 6, row_cnt, normal_font, ANSItoUTF8("                             1"), 8, aligment_left, NORMAL_BG_COLOR, border_outside);	//	MAC 주소 설정 제품 수량 기록

//		excel.set_cell_Value(ws, 2, row_cnt, 3, row_cnt, List_subtitle_font, "      정상 판별 제품 수량", 5, aligment_left, TITLE_BG_COLOR, border_outside);	//	불량 제품
//		excel.set_cell_Value(ws, 4, row_cnt, 6, row_cnt, normal_font, ANSItoUTF8("                             1"), 8, aligment_left, NORMAL_BG_COLOR, border_outside);	//	불량제품 수량

		row_cnt += 2;	//	<< 1칸 띄우기 >>
		// 2. 검사 비콘 리스트 제목 및 분류
		excel.set_cell_Value(ws, 2, row_cnt, normal_font, "2. MAC 주소 할당 비콘 리스트", 5, aligment_left, NORMAL_BG_COLOR, border_No_side);	//	소 제목
		row_cnt++;	//	<< 다음줄 선택 >>
		excel.set_cell_Value(ws, 2, row_cnt, List_subtitle_font, "순서", 5, aligment_center, TITLE_BG_COLOR, border_outside);			//	순번
		excel.set_cell_Value(ws, 3, row_cnt, List_subtitle_font, "고유 MAC 주소", 20, aligment_center, TITLE_BG_COLOR, border_outside);	//	고유 MAC 주소
		excel.set_cell_Value(ws, 4, row_cnt, List_subtitle_font, "할당 MAC 주소", 20, aligment_center, TITLE_BG_COLOR, border_outside);	//	할당 MAC 주소
		excel.set_cell_Value(ws, 5, row_cnt, List_subtitle_font, "전원 전압", 10, aligment_center, TITLE_BG_COLOR, border_outside);	//	전원 전압
		excel.set_cell_Value(ws, 6, row_cnt, List_subtitle_font, "결과 상태", 10, aligment_center, TITLE_BG_COLOR, border_outside);	//	검사 결과

		excel_file_handle.now_row = row_cnt + 1;
		excel_file_handle.list_number = 1;
	}
	else
	{
		excel_now_row_Search(ws, excel_file_handle, 2, "순서");
	}
}


void Beacon_control::excel_MAC_Address_Allocation_Report_list_write(xlnt::worksheet& ws, xlnt::workbook& wb, SCAN_DATA ListBefore, SCAN_DATA ListAfter, EXCEL_FILE_HANDLE_TYPE& excel_file_handle)
{
	char temp[_MAX_PATH];

	int now_row = excel_file_handle.now_row;

	//	이하 내용 완성 ( 실 검사 리스트 작성 )
	int Complete_Quantity_now = 0;

	excel.set_cell_Value(ws, 2, now_row, normal_font, excel_file_handle.list_number, NORMAL_BG_COLOR, border_outside);	//	순번

	sprintf_s(temp, _MAX_PATH, "%02X:%02X:%02X:%02X:%02X:%02X"
		, ListBefore.mac.d8bit[5]
		, ListBefore.mac.d8bit[4]
		, ListBefore.mac.d8bit[3]
		, ListBefore.mac.d8bit[2]
		, ListBefore.mac.d8bit[1]
		, ListBefore.mac.d8bit[0]);
	excel.set_cell_Value(ws, 3, now_row, normal_font, temp, NORMAL_BG_COLOR, border_outside);			//	고유 MAC 주소

	sprintf_s(temp, _MAX_PATH, "%02X:%02X:%02X:%02X:%02X:%02X"
		, ListAfter.mac.d8bit[5]
		, ListAfter.mac.d8bit[4]
		, ListAfter.mac.d8bit[3]
		, ListAfter.mac.d8bit[2]
		, ListAfter.mac.d8bit[1]
		, ListAfter.mac.d8bit[0]);
	excel.set_cell_Value(ws, 4, now_row, normal_font, temp, NORMAL_BG_COLOR, border_outside);		//	할당 MAC 주소

	sprintf_s(temp, _MAX_PATH, "%.1f V", (float)ListAfter.sub_data[0] / 10.0f);
	excel.set_cell_Value(ws, 5, now_row, normal_font, temp, NORMAL_BG_COLOR, border_outside);		//	전원 전압

	excel.set_cell_Value(ws, 6, now_row, blue_Color_font, "정상", NORMAL_BG_COLOR, border_outside);	//	검사 결과

	// 1. 결과 보고 ( 내용 )
	Complete_Quantity_now = excel.cell_Word_search_and_count(ws, 6, now_row - excel_file_handle.list_number, 6, now_row, "정상");

	sprintf_s(temp, _MAX_PATH, "                         %5d", Complete_Quantity_now);
	excel.set_cell_Value(ws, 4, 6, 6, 6, normal_font, ANSItoUTF8(temp), 20, aligment_left, NORMAL_BG_COLOR, border_outside);	//	MAC 주소 설정 제품 수량 기록

	excel_file_handle.now_row = now_row + 1;

}

void Beacon_control::BLE_CMD_Mac_Addr_Set(unsigned char *Mac_Addr)
{
	BLE_Remote_control_Mac_addr[0] = Mac_Addr[0];
	BLE_Remote_control_Mac_addr[1] = Mac_Addr[1];
	BLE_Remote_control_Mac_addr[2] = Mac_Addr[2];
	BLE_Remote_control_Mac_addr[3] = Mac_Addr[3];
	BLE_Remote_control_Mac_addr[4] = Mac_Addr[4];
	BLE_Remote_control_Mac_addr[5] = Mac_Addr[5];
}

void Beacon_control::BLE_CMD_Auto_isr()
{
	if (BLE_Remote_Contorl_Auto_Enable == 1)
	{
		if (BLE_Remote_Contorl_Auto_Delay_cnt >= BLE_Remote_Contorl_Auto_Delay)
		{
			if (BLE_Remote_Control_Target_Index_Auto <= BLE_Remote_Control_Target_Index_Auto_End)
			{
				BLE_CMD_Mac_Addr_Set(&BLE_Scan_List[BLE_Remote_Control_Target_Index_Auto][1]);
				if (BLE_CMD_TxStart(BLE_Remote_Contorl_Auto_CMD) == 1)
				{
					BLE_Remote_Contorl_Auto_Delay_cnt = 0;
					BLE_Remote_Control_Target_Index_Auto++;
				}

			}
			else
			{
				BLE_Remote_Contorl_Auto_Enable = 0;
			}
		}
		else
		{
			BLE_Remote_Contorl_Auto_Delay_cnt++;
		}
	}
}

int Beacon_control::BLE_CMD_TxStart(int CMD)
{
	int result = 0;

	if (BLE_CMD_Enable == 0)
	{
		BLE_CMD_Enable = 1;
		BLE_CMD_Now = CMD;
		BLE_CMD_TxSeq = 2;
		BLE_CMD_Res_Check_Seq = 0;
		Uart_Req_Time_Out = 0;
		result = 1;
	}

	return (result);
}

void Beacon_control::BLE_CMD_TxStart_Erase()
{
	BLE_CMD_Enable = 0;
	BLE_CMD_Now = 0;
	BLE_CMD_TxSeq = 0;
	BLE_CMD_Res_Check_Seq = 0;
	Uart_Req_Time_Out = 0;
}

void Beacon_control::BLE_CMD_TxRestart()
{
	BLE_CMD_TxSeq = 2;
	BLE_CMD_Res_Check_Seq = 0;
}

int Beacon_control::BLE_MAC_Address_Setting_TxStart()
{
	int result = 0;

	if (BLE_CMD_Enable == 0)
	{
		BLE_CMD_Enable = 1;

		BLE_CMD_TxSeq = 5;
		BLE_CMD_Res_Check_Seq = 0;
		Uart_Req_Time_Out = 0;

		result = 1;
	}

	return (result);
}

void Beacon_control::BLE_MAC_Address_Setting_TxRestart()
{
	BLE_CMD_TxSeq = 5;
	BLE_CMD_Res_Check_Seq = 0;
}


int BLE_CMD_Auto_set(char cmd, int Target_total_quantity)
{
	int result = 0;

	if (BLE_Remote_Contorl_Auto_Enable == 0)
	{
		BLE_Remote_Contorl_Auto_CMD = cmd;
		BLE_Remote_Contorl_Auto_Delay = 20;
		BLE_Remote_Contorl_Auto_Delay_cnt = 0;
		BLE_Remote_Control_Target_Index_Auto = 0;
		BLE_Remote_Control_Target_Index_Auto_End = Target_total_quantity - 1;
		BLE_Remote_Contorl_Auto_Enable = 1;
//		CMD_Progress_set(0, Target_total_quantity);
	}

	return (result);
}

void BLE_list_Clear(BLE_SCAN_LIST *List)
{
	List->cnt = 0;
	List->Registered_Quantity = 0;
	for (int cnt = 0; cnt < BLE_SCAN_LIST_MAX; cnt++)
	{
		List->data[cnt].mac.d64bit = 0;
		List->data[cnt].sub_data[0] = 0;
		List->data[cnt].sub_data[1] = 0;
		List->data[cnt].State = 0;
	}
}

void BLE_List_Copy(BLE_SCAN_LIST *Write_List, BLE_SCAN_LIST *Read_List)
{
	Write_List->cnt = Read_List->cnt;
	Write_List->Registered_Quantity = Read_List->Registered_Quantity;
	for (int cnt = 0; cnt < BLE_SCAN_LIST_MAX; cnt++)
	{
		Write_List->data[cnt].mac.d64bit = Read_List->data[cnt].mac.d64bit;
		Write_List->data[cnt].sub_data[0] = Read_List->data[cnt].sub_data[0];
		Write_List->data[cnt].sub_data[1] = Read_List->data[cnt].sub_data[1];
		Write_List->data[cnt].Power_State = Read_List->data[cnt].Power_State;
	}
}

int Beacon_control::BLE_List_RemoveAt(BLE_SCAN_LIST *List, int Index)
{
	int result = 0;

	if ((Index >= 0) && (Index < BLE_SCAN_LIST_MAX))
	{
		for (int cnt = Index; cnt < List->Registered_Quantity - 1; cnt++)
		{
			//	현 지점부터 1개씩 다음 순번의 저장내용 복사
			List->data[cnt].mac.d64bit = List->data[cnt + 1].mac.d64bit;
			List->data[cnt].sub_data[0] = List->data[cnt + 1].sub_data[0];
			List->data[cnt].sub_data[1] = List->data[cnt + 1].sub_data[1];
			List->data[cnt].State = List->data[cnt + 1].State;
			List->data[cnt].Power_State = List->data[cnt + 1].Power_State;
			List->data[cnt].Command_processing_result = List->data[cnt + 1].Command_processing_result;
		}
		//	가장 마지막 1개는 삭제
		List->data[List->Registered_Quantity - 1].mac.d64bit = 0;
		List->data[List->Registered_Quantity - 1].sub_data[0] = 0;
		List->data[List->Registered_Quantity - 1].sub_data[1] = 0;
		List->data[List->Registered_Quantity - 1].State = 0;
		List->data[List->Registered_Quantity - 1].Power_State = 0;
		List->data[List->Registered_Quantity - 1].Command_processing_result = 0;

		//	전체 수량 -1;
		List->cnt -= 1;
		List->Registered_Quantity -= 1;

		result = 1;
	}
	else
	{
		result = -1;
	}

	return (result);
}

int BLE_list_Complete_Registration(BLE_SCAN_LIST *Register_List, SCAN_DATA *Settting_Data)
{
	int result = 0;

	if (Register_List->cnt < BLE_SCAN_LIST_MAX)
	{
		Register_List->data[Register_List->cnt].mac.d64bit = Settting_Data->mac.d64bit;
		Register_List->data[Register_List->cnt].sub_data[0] = Settting_Data->sub_data[0];
		Register_List->data[Register_List->cnt].sub_data[1] = Settting_Data->sub_data[1];

		Register_List->cnt++;
		Register_List->Registered_Quantity = Register_List->cnt;

		result = 1;
	}

	return (result);
}

void Beacon_control::BLE_ALL_Auto_Process_init()
{
	BLE_SCAN_LIST *CompleteList = &BLE_Scanner_list_Control_Dummy;
	BLE_SCAN_LIST *ReadList = &BLE_Scanner.list.After;
	int CMD = CMD_POWER_OFF;

	//	기존 실행중인 명령어 모드 상태 초기화 
	BLE_CMD_TxStart_Erase();
	this->BLE_MAC_Address_Setting_Auto_Process = 0;

	BLE_Scanner_list_Control_All_Complete = CompleteList;
	BLE_list_Clear(BLE_Scanner_list_Control_All_Complete);	//	완료 리스트 삭제
	BLE_List_Copy(&BLE_Scanner_list_Control_All, ReadList);	//	실행 리스트 등록
	BLE_ALL_Auto_CMD = CMD;
	BLE_ALL_Auto_Enable_flag = 1;
	BLE_ALL_Auto_Process_Delay = 0;
//	CMD_Progress_set(0, ReadList->Registered_Quantity);
}

int Beacon_control::BLE_list_Registeri_Check(SCAN_MAC_ADDR_DATA *Check_mac, BLE_SCAN_LIST *List)
{
	int result = 0;

	if (List->Registered_Quantity > 0)
	{
		for (int cnt = 0; cnt < List->Registered_Quantity; cnt++)
		{
			if (Check_mac->d64bit == List->data[cnt].mac.d64bit)
			{
				result = 1;
				return (result);
			}
		}
	}

	return (result);
}

int Beacon_control::BLE_list_Registeri_Index_Read(SCAN_MAC_ADDR_DATA *Check_mac, BLE_SCAN_LIST *List)
{
	int index = BLE_SCAN_LIST_MAX;

	if (List->Registered_Quantity > 0)
	{
		for (int cnt = 0; cnt < List->Registered_Quantity; cnt++)
		{
			if (Check_mac->d64bit == List->data[cnt].mac.d64bit)
			{
				index = cnt;
				return (index);
			}
		}
	}

	return (index);
}

void Beacon_control::BLE_All_Auto_Process()
{
	unsigned char mac_address[6] = { 0 };

	if (BLE_ALL_Auto_Enable_flag == 1)
	{
		if (++BLE_ALL_Auto_Process_Delay >= 20)
		{
			BLE_ALL_Auto_Process_Delay = 0;

			if (BLE_ALL_Auto_Seq == 0)
			{
				for (int cnt = 0; cnt < BLE_Scanner_list_Control_All.Registered_Quantity; cnt++)
				{
					if (BLE_Scanner_list_Control_All.data[cnt].Power_State == 1)
					{
						if (BLE_list_Registeri_Check(&BLE_Scanner_list_Control_All.data[cnt].mac, BLE_Scanner_list_Control_All_Complete) == 0)
						{
							if (BLE_Scanner_list_Control_All.data[cnt].mac.d64bit != 0)
							{
								mac_address[0] = BLE_Scanner_list_Control_All.data[cnt].mac.d8bit[5];
								mac_address[1] = BLE_Scanner_list_Control_All.data[cnt].mac.d8bit[4];
								mac_address[2] = BLE_Scanner_list_Control_All.data[cnt].mac.d8bit[3];
								mac_address[3] = BLE_Scanner_list_Control_All.data[cnt].mac.d8bit[2];
								mac_address[4] = BLE_Scanner_list_Control_All.data[cnt].mac.d8bit[1];
								mac_address[5] = BLE_Scanner_list_Control_All.data[cnt].mac.d8bit[0];
								BLE_ALL_Auto_Control_Data.mac.d64bit = BLE_Scanner_list_Control_All.data[cnt].mac.d64bit;
								BLE_ALL_Auto_Control_Data.sub_data[0] = BLE_Scanner_list_Control_All.data[cnt].sub_data[0];
								BLE_ALL_Auto_Control_Data.sub_data[1] = BLE_Scanner_list_Control_All.data[cnt].sub_data[1];

								BLE_CMD_Mac_Addr_Set(mac_address);
								if (BLE_CMD_TxStart(BLE_ALL_Auto_CMD) == 1)
								{
									BLE_Scanner.list.After.data[cnt].Command_processing_result = 0;
									BLE_Scanner.Command_processing_result = &BLE_Scanner.list.After.data[cnt].Command_processing_result;
								}

								BLE_ALL_Auto_Seq = 1;
								break;
							}
						}
					}
				}
			}
			else if (BLE_ALL_Auto_Seq == 2)
			{
				BLE_list_Complete_Registration(BLE_Scanner_list_Control_All_Complete, &BLE_ALL_Auto_Control_Data);
				if (BLE_Scanner.Command_processing_result != 0)
				{//	명령 처리 완료 결과 통보
					*(BLE_Scanner.Command_processing_result) = 1;
				}
				BLE_ALL_Auto_Seq = 0;
			}

		}
	}


}


void Beacon_control::BLE_List_Cmd_Process_init()
{
	BLE_SCAN_LIST *ReadList = &BLE_Scanner_list[BLE_SCANNER_LIST_MANUFACTURE];
	int CMD = CMD_POWER_OFF;

	//	기존 실행중인 명령어 모드 상태 초기화 
	BLE_CMD_TxStart_Erase();

	BLE_Scanner.list.CMD = CMD;
	BLE_Scanner.list.cmd_Enable_flag = 1;
	BLE_Scanner.list.Delay = 0;

	BLE_list_Clear(&BLE_Scanner.list.fixing);
	BLE_List_Copy(&BLE_Scanner.list.fixing, ReadList);	//	실행 리스트 등록
	BLE_Scanner.Hardware_test.Inspection_Quantity = BLE_Scanner.list.fixing.Registered_Quantity;

//	CMD_Progress_set(0, ReadList->Registered_Quantity);
	BLE_Scanner.Hardware_test.Complete_Quantity_now = 0;
	BLE_Scanner.Hardware_test.Defect_Product_Quantity_now = 0;
	BLE_Scanner.Hardware_test.Re_inspection_Quantity = 0;
}

void Beacon_control::BLE_List_Cmd_Process_Clear()
{
	BLE_list_Clear(&BLE_Scanner.list.fixing);
	BLE_Scanner.Hardware_test.Complete_Quantity_now = 0;
	BLE_Scanner.Hardware_test.Defect_Product_Quantity_now = 0;
	BLE_Scanner.Hardware_test.Re_inspection_Quantity = 0;
}

void Beacon_control::BLE_List_Cmd_Fixing_Reload(BLE_SCAN_LIST *List)
{
	if (BLE_Scanner.list.cmd_Enable_flag == 0)
	{
		BLE_list_Clear(&BLE_Scanner.list.fixing);
		BLE_List_Copy(&BLE_Scanner.list.fixing, List);	//	실행 리스트 등록
		BLE_Scanner.Hardware_test.Inspection_Quantity = BLE_Scanner.list.fixing.Registered_Quantity;
	}
}

void Beacon_control::BLE_Scan_Hardware_Test_View_init(void)
{
	if (BLE_Scan_Hardware_Test_View_init_flag == 0)
	{
		BLE_Scan_Hardware_Test_View_init_flag = 1;
		BLE_List_Cmd_Fixing_Reload(&BLE_Scanner_list[BLE_Data_Type]);
	}
}


void Beacon_control::BLE_List_Cmd_Process()
{
	unsigned char mac_address[6] = { 0 };

	if (BLE_Scanner.list.cmd_Enable_flag == 1)
	{
		if (++BLE_Scanner.list.Delay >= 20)
		{
			BLE_Scanner.list.Delay = 0;

			for (int cnt = 0; cnt < BLE_Scanner.list.fixing.Registered_Quantity;)
			{
				if (BLE_Scanner.list.fixing.data[cnt].State == 0)
				{
					if (BLE_Scanner.list.fixing.data[cnt].mac.d64bit != 0)
					{
						if (BLE_Scanner.list.fixing.data[cnt].sub_data[0] < this->Hardware_test_Allowable_voltage)
						{//	검사 대기중 비콘의 배터리 전압이 허용전압 보다 낮은 상태로 제품에는 이상이 없으므로 배터리 교체 후 재검사 수행
							BLE_Scanner.list.fixing.data[cnt].State = 4;
							BLE_Scanner.Hardware_test.Re_inspection_Quantity++;
							cnt++;
						}
						else
						{//	정상일 경우 비콘 전원 OFF 명령을 스캐너에게 하달
							BLE_Scanner.list.fixing.cmd_now_index = cnt;
							mac_address[0] = BLE_Scanner.list.fixing.data[cnt].mac.d8bit[5];
							mac_address[1] = BLE_Scanner.list.fixing.data[cnt].mac.d8bit[4];
							mac_address[2] = BLE_Scanner.list.fixing.data[cnt].mac.d8bit[3];
							mac_address[3] = BLE_Scanner.list.fixing.data[cnt].mac.d8bit[2];
							mac_address[4] = BLE_Scanner.list.fixing.data[cnt].mac.d8bit[1];
							mac_address[5] = BLE_Scanner.list.fixing.data[cnt].mac.d8bit[0];

							BLE_CMD_Mac_Addr_Set(mac_address);
							if (BLE_CMD_TxStart(BLE_Scanner.list.CMD) == 1)
							{
								BLE_Scanner.list.fixing.data[cnt].State = 1;
								break;
							}
						}
					}
				}//	Uart 통신을 통해 비콘 OFF 명령 실행 완료 보고 받을시 다음 순서 비콘으로 진행
				else if (BLE_Scanner.list.fixing.data[cnt].State == 2)	//	1개의 비콘 검사 완료 확인
				{
					BLE_Scanner.Hardware_test.Complete_Quantity_now++;
					excel_Hardware_Test_Report(BLE_Scanner.list.fixing.data[cnt], excel_file_handle_list[EXCEL_FILE_HW_TEST_REPORT]);
					BLE_Scanner.list.fixing.data[cnt].State = 3;
					cnt++;
				}
				else if (BLE_Scanner.list.fixing.data[cnt].State >= 3)
				{
					cnt++;
				}
				else
				{
					break;
				}
			}

			if ((BLE_Scanner.Hardware_test.Complete_Quantity_now + BLE_Scanner.Hardware_test.Defect_Product_Quantity_now + BLE_Scanner.Hardware_test.Re_inspection_Quantity)
				>= BLE_Scanner.Hardware_test.Inspection_Quantity)
			{
				BLE_Scanner.Hardware_test.Defect_Product_Quantity += BLE_Scanner.Hardware_test.Defect_Product_Quantity_now;
				BLE_Scanner.Hardware_test.Complete_Quantity += BLE_Scanner.Hardware_test.Complete_Quantity_now;
				BLE_Scanner.list.cmd_Enable_flag = 2;

				this->hardware_test_complete = 1;
				//					Hardware_Test_Disable();
			}
			else
			{
				this->hardware_test_complete = 0;
			}

		}
	}


}

		//PS1FFFFFFFFFFFFC20194000003cc$0d$0a
void Beacon_control::BLE_MAC_Address_Set_Enable(unsigned char *Addr_Now, unsigned char *Addr_New)
{
	//	변경 할 MAC 주소 설정
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][0] = Addr_Now[0];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][1] = Addr_Now[1];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][2] = Addr_Now[2];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][3] = Addr_Now[3];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][4] = Addr_Now[4];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][5] = Addr_Now[5];

	//	신규 MAC 주소 설정
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][0] = Addr_New[0];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][1] = Addr_New[1];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][2] = Addr_New[2];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][3] = Addr_New[3];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][4] = Addr_New[4];
	Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][5] = Addr_New[5];

	BLE_MAC_Address_Setting_TxStart();
	BLE_MAC_Address_Setting_Auto_Process_flag = 1;
}

void Beacon_control::BLE_MAC_Address_Setting_Process(System::Windows::Forms::TextBox^  Next_MAC_num_textBox, System::Windows::Forms::TextBox^  Month_textBox)
{
	unsigned char month = 0;
	int Index = BLE_SCAN_LIST_MAX;
	int Index_FI = BLE_SCAN_LIST_MAX;

	if (++BLE_MAC_Address_Setting_Auto_Process_Delay >= 20)
	{
		if (this->BLE_MAC_Address_Setting_Auto_Process == 1)
		{
			if (BLE_MAC_Address_Setting_Auto_Process_flag == 0)
			{
				for (int cnt = 0; cnt <= BLE_Scanner.list.Before.Registered_Quantity;)
				{
					if (BLE_Scanner.list.Before.data[cnt].State == 3)	//	설정완료 : 다음 순서로
					{
						cnt++;
					}
					else if (BLE_Scanner.list.Before.data[cnt].State == 1)	//	 설정 중 : 응답 대기
					{
						break;
					}
					else if (BLE_Scanner.list.Before.data[cnt].State == 0)	//	 신규 설정 : 신규 설정 적용
					{
						for (int new_list_Cnt = 0; new_list_Cnt < BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].Registered_Quantity; new_list_Cnt++)
						{
							if ((BLE_list_Registeri_Check(&BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac, &BLE_Scanner.list.After) == 0)
								&& (BLE_list_Registeri_Check(&BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac, &BLE_Scanner.list.Before) == 0))
							{
								if (BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d64bit != 0)
								{
									//	변경 할 MAC 주소 설정
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][0] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d8bit[5];
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][1] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d8bit[4];
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][2] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d8bit[3];
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][3] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d8bit[2];
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][4] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d8bit[1];
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][5] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac.d8bit[0];


									MAC_Address_Setting_Data_Revocation.mac.d8bit[5] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][0];
									MAC_Address_Setting_Data_Revocation.mac.d8bit[4] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][1];
									MAC_Address_Setting_Data_Revocation.mac.d8bit[3] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][2];
									MAC_Address_Setting_Data_Revocation.mac.d8bit[2] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][3];
									MAC_Address_Setting_Data_Revocation.mac.d8bit[1] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][4];
									MAC_Address_Setting_Data_Revocation.mac.d8bit[0] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][5];

									New_Mac_Number = (int)(Convert::ToInt32(Next_MAC_num_textBox->Text));
									month = (unsigned char)(Convert::ToByte(Month_textBox->Text));

									//	신규 MAC 주소 설정
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][0] = 0xC2;
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][1] = 0x01;
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][2] = 0x90 | month;
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][3] = (unsigned char)((New_Mac_Number & 0xff0000) >> 16);
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][4] = (unsigned char)((New_Mac_Number & 0x00ff00) >> 8);
									Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][5] = (unsigned char)(New_Mac_Number & 0x0000ff);

									MAC_Address_Setting_Data.mac.d8bit[5] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][0];
									MAC_Address_Setting_Data.mac.d8bit[4] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][1];
									MAC_Address_Setting_Data.mac.d8bit[3] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][2];
									MAC_Address_Setting_Data.mac.d8bit[2] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][3];
									MAC_Address_Setting_Data.mac.d8bit[1] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][4];
									MAC_Address_Setting_Data.mac.d8bit[0] = Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][5];

									if (BLE_Scanner.list.Before.cnt < BLE_SCAN_LIST_MAX)
									{
										BLE_Scanner.list.Before.data[BLE_Scanner.list.Before.cnt].mac.d64bit = MAC_Address_Setting_Data_Revocation.mac.d64bit;	//	변경전 MAC 주소
										BLE_Scanner.list.After.data[BLE_Scanner.list.After.cnt].mac.d64bit = MAC_Address_Setting_Data.mac.d64bit;				//	변경될 MAC 주소

										BLE_Scanner.list.After.data[BLE_Scanner.list.After.cnt].sub_data[0] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].sub_data[0];
										BLE_Scanner.list.After.data[BLE_Scanner.list.After.cnt].sub_data[1] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].sub_data[1];


										BLE_Scanner.list.After.data[BLE_Scanner.list.Before.cnt].Power_State = 1;
										BLE_Scanner.list.Before.data[BLE_Scanner.list.Before.cnt].State = 1;
										BLE_Scanner.list.Before.cmd_now_index = BLE_Scanner.list.Before.cnt;

										BLE_Scanner.list.Before.cnt++;
										BLE_Scanner.list.Before.Registered_Quantity = BLE_Scanner.list.Before.cnt;

										BLE_Scanner.list.After.cnt++;
										BLE_Scanner.list.After.Registered_Quantity = BLE_Scanner.list.Before.cnt;
									}

									BLE_MAC_Address_Setting_TxStart();

									BLE_MAC_Address_Setting_Auto_Process_flag = 1;
								}
								break;
							}
						}
						break;
					}

				}

			}
			else if (BLE_MAC_Address_Setting_Auto_Process_flag == 2)
			{
				if (BLE_Scanner.list.Before.data[BLE_Scanner.list.Before.cmd_now_index].State == 1)
				{
					BLE_Scanner.list.Before.data[BLE_Scanner.list.Before.cmd_now_index].State = 3;
					excel_MAC_Address_Allocation_Report(BLE_Scanner.list.Before.data[BLE_Scanner.list.Before.cmd_now_index], BLE_Scanner.list.After.data[BLE_Scanner.list.Before.cmd_now_index], excel_file_handle_list[EXCEL_FILE_MAC_ALLOC_REPORT]);

				}

				//					BLE_list_Complete_Registration(&BLE_Scanner_list_Complete[BLE_SCANNER_LIST_MAC_ADDR_SET], &MAC_Address_Setting_Data);	//	완료 Mac Address 리스트
				//					BLE_list_Complete_Registration(&BLE_Scanner_list_Revocation[BLE_SCANNER_LIST_MAC_ADDR_SET], &MAC_Address_Setting_Data_Revocation);	//	기존 Mac Address 리스트 

				BLE_MAC_Address_Setting_Auto_Process_flag = 0;
				Next_MAC_num_textBox->Text = String::Format("{0}", New_Mac_Number + 1);
				ini_lib.write_INI_Value("BeaconScanner", "NEXT_MAC_ADDRESS", Next_MAC_num_textBox->Text, TEXT(".\\BeaconScanner.ini"));

			}
		}

		BLE_Scanner.Mac_Address_setting.Complete_Quantity_now = 0;
		for (int cnt = 0; cnt <= BLE_Scanner.list.Before.Registered_Quantity; cnt++)
		{
			if (BLE_Scanner.list.Before.data[cnt].State == 3)
			{
				BLE_Scanner.Mac_Address_setting.Complete_Quantity_now++;
			}
		}
		BLE_Scanner.Mac_Address_setting.Complete_Quantity = BLE_Scanner.Mac_Address_setting.Complete_Quantity_now;

		for (int new_list_Cnt = 0; new_list_Cnt < BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].Registered_Quantity; new_list_Cnt++)
		{
			if (BLE_list_Registeri_Check(&BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac, &BLE_Scanner.list.After) == 1)
			{
				Index = BLE_list_Registeri_Index_Read(&BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].mac, &BLE_Scanner.list.After);
				if (Index < BLE_SCAN_LIST_MAX)
				{
					BLE_Scanner.list.After.data[Index].sub_data[0] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].sub_data[0];
					BLE_Scanner.list.After.data[Index].sub_data[1] = BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].sub_data[1];
					if (BLE_Scanner_list[BLE_SCANNER_LIST_MAC_ADDR_SET].data[new_list_Cnt].sub_data[1] == 1)
					{
						Index_FI = Index;
					}
				}
			}

		}

		BLE_MAC_Address_Setting_Auto_Process_Delay = 0;
	}

}

int Uart_Q_push(UART_DATA_QUEUE *uart_q, unsigned char data)
{
	if (((uart_q->tail + 1) % UART_DATA_QUEUE_MAX) == uart_q->head)
	{
		return FALSE;
	}

	uart_q->data[uart_q->tail] = data;

	uart_q->tail = (uart_q->tail + 1) % UART_DATA_QUEUE_MAX;

	return TRUE;
}

int Uart_Q_pop(UART_DATA_QUEUE *uart_q, unsigned char *data)
{
	if (uart_q->head == uart_q->tail)
	{
		return FALSE;
	}

	*data = uart_q->data[uart_q->head];

	uart_q->head = (uart_q->head + 1) % UART_DATA_QUEUE_MAX;

	return TRUE;
}

int BLE_Scan_List_Q_push(unsigned char *data_Buff, SCAN_LIST_QUEUE * queue)
{
	if (((queue->tail + 1) % BLE_SCAN_LIST_QUEUE_MAX) == queue->head)
	{
		return FALSE;
	}

	queue->data[queue->tail].mac.d8bit[0] = data_Buff[6];
	queue->data[queue->tail].mac.d8bit[1] = data_Buff[5];
	queue->data[queue->tail].mac.d8bit[2] = data_Buff[4];
	queue->data[queue->tail].mac.d8bit[3] = data_Buff[3];
	queue->data[queue->tail].mac.d8bit[4] = data_Buff[2];
	queue->data[queue->tail].mac.d8bit[5] = data_Buff[1];

	queue->data[queue->tail].sub_data[0] = data_Buff[0];
	queue->data[queue->tail].sub_data[1] = data_Buff[7];

	queue->tail = (queue->tail + 1) % BLE_SCAN_LIST_QUEUE_MAX;

	return TRUE;
}


int BLE_Scan_List_Q_pop(SCAN_LIST_QUEUE * queue, SCAN_DATA *pop_data)
{
	if (queue->head == queue->tail)
	{
		return FALSE;
	}

	pop_data->mac = queue->data[queue->head].mac;
	pop_data->sub_data[0] = queue->data[queue->head].sub_data[0];
	pop_data->sub_data[1] = queue->data[queue->head].sub_data[1];

	queue->head = (queue->head + 1) % UART_DATA_QUEUE_MAX;

	return TRUE;

}

int BLE_Scan_List_Q_empty(SCAN_LIST_QUEUE * queue)
{
	if (queue->head == queue->tail)
	{
		return TRUE;
	}

	return FALSE;
}

void BLE_Scan_List_Q_init()
{
	BLE_Scanner.copyBuff_Cnt = 0;
}

int BLE_Scan_List_Q_insert(unsigned char data, SCAN_LIST_QUEUE * queue, int limit_length, int Registered_Quantity)
{
	if (BLE_Scanner.copyBuff_Cnt < (Registered_Quantity * 8))
	{
		BLE_Scanner.copyBuff[BLE_Scanner.copyBuff_Cnt] = data;
		if (++BLE_Scanner.copyBuff_Cnt >= limit_length)
		{
			BLE_Scanner.copyBuff_Cnt = 0;
			BLE_Scan_List_Q_push((unsigned char *)&(BLE_Scanner.copyBuff[0]), queue);
		}
	}

	return TRUE;
}

void Beacon_control::Qpush_serial_1_Rx_Buffer(System::IO::Ports::SerialPort^ serialPort)
{
	int Length = 100;
	unsigned char readByte = 0;

	RxCnt++;

	if (serialPort->IsOpen)
	{
		Length = serialPort->BytesToRead;

		if (Length > 0)
		{
			for (int cnt = 0; cnt < Length; cnt++)
			{
				if (serialPort->IsOpen)
				{
					readByte = (unsigned char)serialPort->ReadByte();
					Uart_Q_push(&Uart1, readByte);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void BLE_Scan_List_Registering_init(BLE_SCAN_LIST *List, int fixing, int Registered_Quantity)
{
	if (fixing == 0)
	{
		for (int cnt = 0; cnt < BLE_SCAN_LIST_MAX; cnt++)
		{
			List->data[cnt].mac.d64bit = 0;
			List->data[cnt].sub_data[0] = 0;
			List->data[cnt].sub_data[1] = 0;
		}

		List->cnt = 0;
		List->Registered_Quantity = Registered_Quantity;
	}
}

void BLE_Scan_List_Registering(BLE_SCAN_LIST *List, SCAN_LIST_QUEUE * queue, int fixing)
{
	SCAN_DATA read_data = { 0 };
	int registration_confirmation = 0;
	int Registered_Quantity = 0;


	while (BLE_Scan_List_Q_pop(queue, &read_data) == TRUE)
	{
		for (int cnt = 0; cnt < List->cnt; cnt++)
		{
			if (List->data[cnt].mac.d64bit == read_data.mac.d64bit)
			{
				registration_confirmation = 1;
			}
		}

		if (registration_confirmation == 0)
		{
			if (List->cnt < BLE_SCAN_LIST_MAX)
			{
				List->data[List->cnt].mac.d64bit = read_data.mac.d64bit;
				List->data[List->cnt].sub_data[0] = read_data.sub_data[0];
				List->data[List->cnt].sub_data[1] = read_data.sub_data[1];

				List->cnt++;
			}
		}

		Registered_Quantity = List->cnt;
	}

	if (fixing == 1)
	{
		if (Registered_Quantity >= List->Registered_Quantity)
		{
			List->Registered_Quantity = Registered_Quantity;
		}
	}

}

void Beacon_control::Uart_tickISR()
{
	Uart_rx_Time_Out += 20;
	Uart_Req_Time_Out += 20;
}

void Beacon_control::BLE_CMD_Tick_isr(System::IO::Ports::SerialPort^  serialPort)
{

	if (BLE_CMD_Enable == 1)
	{
		if (Uart_Req_Time_Out >= 500)
		{
			Uart_Req_Time_Out = 0;
			if (BLE_MAC_Address_Setting_Auto_Process_flag == 1)
			{
				BLE_MAC_Address_Setting_TxRestart();
			}
			else
			{
				BLE_CMD_TxRestart();
			}
		}

		if (serialPort->IsOpen) {
			switch (BLE_CMD_TxSeq)
			{
			case 1:
				if (BLE_CMD_Res_Check_Seq == 0)
				{
					CMD_MODE_ON(serialPort, "0");
					BLE_CMD_Res_Check_Seq = BLE_CMD_TxSeq;
				}
				break;
			case 2:
				if (Uart_Req_Time_Out >= RESTART_TIME)
				{
					Uart_Req_Time_Out = 0;
					CMD_BLE_Scanner(serialPort, BLE_CMD_Now, BLE_Remote_control_Mac_addr);
					BLE_CMD_Res_Length = sprintf_s((char *)BLE_CMD_TxRes_Check_Buff, 100, "%c[%02X%02X%02X%02X%02X%02X]", BLE_CMD_Now
						, BLE_Remote_control_Mac_addr[0]
						, BLE_Remote_control_Mac_addr[1]
						, BLE_Remote_control_Mac_addr[2]
						, BLE_Remote_control_Mac_addr[3]
						, BLE_Remote_control_Mac_addr[4]
						, BLE_Remote_control_Mac_addr[5]
					);
				}
				break;
			case 3:
				if (Uart_Req_Time_Out >= RESTART_TIME)
				{
					Uart_Req_Time_Out = 0;
					CMD_BLE_Scanner_Request(serialPort, BLE_CMD_Now, BLE_Remote_control_Mac_addr);
					BLE_CMD_Res_Check_Seq = BLE_CMD_TxSeq;
				}
				break;
			case 4:
				if (BLE_ALL_Auto_Seq == 1)
				{
					BLE_ALL_Auto_Seq = 2;
				}
				else if (this->BLE_MAC_Address_Setting_Auto_Process == 1)
				{
					this->BLE_MAC_Address_Setting_Auto_Process = 2;
				}
				else if (BLE_Scanner.list.fixing.data[BLE_Scanner.list.fixing.cmd_now_index].State == 1)
				{
					BLE_Scanner.list.fixing.data[BLE_Scanner.list.fixing.cmd_now_index].State = 2;
				}
				else
				{
//					Button_Color_Reset();
				}
				BLE_CMD_TxSeq++;
				BLE_CMD_Enable = 0;
//				CMD_Progress_UP();

				break;

			case 5:
				if (Uart_Req_Time_Out >= RESTART_TIME)
				{
					Uart_Req_Time_Out = 0;
					CMD_BLE_MAC_Address_Setting(serialPort, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW], Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW]);
					BLE_CMD_Res_Length = sprintf_s((char *)BLE_CMD_TxRes_Check_Buff, 100, "[%02X%02X%02X%02X%02X%02X>%02X%02X%02X%02X%02X%02X]"
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][0]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][1]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][2]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][3]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][4]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW][5]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][0]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][1]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][2]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][3]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][4]
						, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW][5]
					);
				}
				break;

			case 6:
				if (Uart_Req_Time_Out >= RESTART_TIME)
				{
					Uart_Req_Time_Out = 0;
					CMD_BLE_MAC_Address_Setting_Request(serialPort, Mac_Address_Set_Buff[MAC_ADDRESS_SET_NOW], Mac_Address_Set_Buff[MAC_ADDRESS_SET_NEW]);
				}
				break;
			case 7:
				if (BLE_MAC_Address_Setting_Auto_Process_flag == 1)
				{
					BLE_MAC_Address_Setting_Auto_Process_flag = 2;
				}
				BLE_CMD_TxSeq++;
				BLE_CMD_Enable = 0;
				break;
			default:
				break;
			}
		}
		else {
//			Button_Color_Reset();
			BLE_CMD_TxSeq = 0;
			BLE_CMD_Enable = 0;
		}

	}

}

int CMD_TxSeq_Check_CNT = 0;

void Beacon_control::BLE_CMD_RxReq_Check(unsigned char data)
{
	int Err_Check_Str_Length = 0;

	Copy_Buff_RES[BLE_RES_RxDataCopy_Cnt] = data;
	if (++BLE_RES_RxDataCopy_Cnt >= 100)BLE_RES_RxDataCopy_Cnt = 0;

	CMD_TxSeq_Check_CNT = 1;
	if (data == 0x0d)
	{
		CMD_TxSeq_Check_CNT = 2;

		switch (BLE_CMD_TxSeq)
		{
		case 2:
			if (Data_Cmp((char *)Copy_Buff_RES, (char *)"ERROR", 5) == 0)
			{
				//					BLE_CMD_TxSeq = 2;
			}

			if (Data_Cmp((char *)&Copy_Buff_RES[15], (char *)"ENABLE", 6) == 0)
			{
				if (Data_Cmp((char *)Copy_Buff_RES, (char *)BLE_CMD_TxRes_Check_Buff, BLE_CMD_Res_Length) == 0)
				{
					BLE_CMD_TxSeq = 3;
				}
			}
			break;
		case 3:
			CMD_TxSeq_Check_CNT = 3;

			if (Data_Cmp((char *)Copy_Buff_RES, (char *)BLE_CMD_TxRes_Check_Buff, BLE_CMD_Res_Length) == 0)
			{
				if (Data_Cmp((char *)&Copy_Buff_RES[15], (char *)"OK", 2) == 0)
				{
					BLE_CMD_TxSeq = 4;
				}
				else if (Data_Cmp((char *)&Copy_Buff_RES[15], (char *)"ING", 3) == 0)
				{

				}
				else if (Data_Cmp((char *)&Copy_Buff_RES[15], (char *)"NONE", 4) == 0)
				{
					BLE_CMD_TxSeq = 2;
				}

			}
			break;
		case 5:
			if (Data_Cmp((char *)&Copy_Buff_RES[27], (char *)"ENABLE", 6) == 0)
			{
				if (Data_Cmp((char *)Copy_Buff_RES, (char *)BLE_CMD_TxRes_Check_Buff, BLE_CMD_Res_Length) == 0)
				{
					BLE_CMD_TxSeq = 6;
				}
			}
			break;
		case 6:
			if (Data_Cmp((char *)Copy_Buff_RES, (char *)BLE_CMD_TxRes_Check_Buff, BLE_CMD_Res_Length) == 0)
			{
				if (Data_Cmp((char *)&Copy_Buff_RES[27], (char *)"OK", 2) == 0)
				{
					BLE_CMD_TxSeq = 7;
				}
				else if (Data_Cmp((char *)&Copy_Buff_RES[27], (char *)"ING", 3) == 0)
				{

				}
				else if (Data_Cmp((char *)&Copy_Buff_RES[27], (char *)"NONE", 4) == 0)
				{
					BLE_CMD_TxSeq = 5;
				}

			}
			break;
			break;
		}

		BLE_RES_RxDataCopy_Cnt = 0;
	}
}

void Beacon_control::BLE_CMD_TxSeq_Check(unsigned char data)
{
	int Err_Check_Str_Length = 0;

	Copy_Buff_CMD[BLE_CMD_RxDataCopy_Cnt] = data;
	if (++BLE_CMD_RxDataCopy_Cnt >= 100)BLE_CMD_RxDataCopy_Cnt = 0;

	if (data == 0x0d)
	{

		if (BLE_CMD_Res_Check_Seq != 0)
		{
			if (Data_Cmp((char *)Copy_Buff_CMD, (char *)"BUSY", 4) == 0)
			{
				Uart_Req_Time_Out = 0;
			}
			else if (Data_Cmp((char *)Copy_Buff_CMD, (char *)"ERROR", 5) == 0)
			{
				BLE_CMD_Res_Check_Seq = 0;
			}
			else if (Data_Cmp((char *)Copy_Buff_CMD, (char *)BLE_CMD_TxRes_Check_Buff, BLE_CMD_Res_Length) == 0)
			{
				BLE_CMD_TxSeq = BLE_CMD_Res_Check_Seq + 1;
				BLE_CMD_Res_Check_Seq = 0;
			}


		}

		BLE_CMD_RxDataCopy_Cnt = 0;
	}
}

void Beacon_control::BLE_Data_Read(unsigned char data)
{
	int *data_Can_Cnt_ptr = 0;
	int *data_Can_Cnt_Before_ptr = 0;

	switch (BLE_Data_RxSeq)
	{
	case 0:
		switch (data)
		{
		case 'B':
			BLE_Data_RxSeq = 10;
			break;
		case 'R':
			BLE_Data_RxSeq = 20;
			break;
		}
		break;
	case 10:
		if (data == 'C')
		{
			BLE_Data_RxSeq = 100;
			BLE_Data_Type = BLE_SCANNER_LIST_NORMAL;
		}
		else
		{
			BLE_Data_RxSeq = 0;
		}
		break;
	case 20:
		if ((data >= '0') && (data <= '3'))
		{
			BLE_Data_RxSeq = 100;
			BLE_Data_Type = data - '0';
		}
		else
		{
			BLE_Data_RxSeq = 0;
		}
		break;

	case 100:
		Item_Num = data;
		BLE_Data_RxSeq = 200;
		BLE_Scan_List_Cnt = 0;
		BLE_Scan_List_renewal = 0;
		BLE_Scan_List_Q_init();
		dataCnt = 0;
		BLE_Scan_List_Registering_init(&BLE_Scanner_list[BLE_Data_Type], 0, Item_Num);
		break;

	case 200:
		if (data == 0x0d)
		{
			BLE_Scan_List_Registering(&BLE_Scanner_list[BLE_Data_Type], &Scan_List_Q[BLE_Data_Type], 0);

			switch (BLE_Data_Type)
			{
			case BLE_SCANNER_LIST_NORMAL:
				break;
			case BLE_SCANNER_LIST_OTHER:
				break;
			case BLE_SCANNER_LIST_CONITE:
				break;
			case BLE_SCANNER_LIST_MANUFACTURE:
				BLE_List_Cmd_Fixing_Reload(&BLE_Scanner_list[BLE_Data_Type]);
				break;
			case BLE_SCANNER_LIST_MAC_ADDR_SET:
				break;

			}
			BLE_Data_RxSeq = 0;
		}
		else
		{
			BLE_Scan_List_Q_insert(data, &Scan_List_Q[BLE_Data_Type], 8, BLE_Scanner_list[BLE_Data_Type].Registered_Quantity);
		}
		break;

	}

}

void Beacon_control::BLE_CMD_Read(unsigned char data)
{

	switch (BLE_CMD_RxSeq)
	{
	case 0:
		if (data == 'S')
		{
			BLE_CMD_RxSeq = 3;
		}
		else if (data == 'C')
		{
			BLE_CMD_RxSeq = 1;
		}
		break;
	case 1:
		if (data == 'M')
		{
			BLE_CMD_RxSeq = 2;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;
	case 2:
		if (data == 'D')
		{
			BLE_CMD_RxSeq = 10;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;

	case 3:
		if (data == 'P')
		{
			BLE_CMD_RxSeq = 4;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;
	case 4:
		if (data == '1')
		{
			BLE_CMD_RxSeq = 5;
		}
		else if (data == '2')
		{
			BLE_CMD_RxSeq = 5;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;
	case 5:
		if (data == 'R')
		{
			BLE_CMD_RxSeq = 6;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;
	case 6:
		if (data == 'E')
		{
			BLE_CMD_RxSeq = 7;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;
	case 7:
		if (data == 'S')
		{
			BLE_CMD_RxSeq = 11;
		}
		else
		{
			BLE_CMD_RxSeq = 0;
		}
		break;

	case 10:
		if (data == 0x0d)
		{
			BLE_CMD_RxSeq = 0;
		}
		else
		{
		}


		break;

	case 11:
		BLE_CMD_RxReq_Check(data);

		if (data == 0x0d)
		{
			BLE_CMD_RxSeq = 0;
		}

		break;

	}

}

void Beacon_control::serialPort_decoder_Execution(int index, unsigned char *Check_Buff)
{// 최종 판단 실행부
	switch (index)
	{
	case SERIAL1_DATA_TYPE_CMD_0:
		if (Data_Cmp((char *)Check_Buff, (char *)"0ON", 3) == 0)
		{
			this->BLE_Scanner_connection = 1;
		}
		else if (Data_Cmp((char *)Check_Buff, (char *)"0OF", 3) == 0)
		{
			this->BLE_Scanner_connection = 0;
		}
		break;
	default:
		break;
	}
}



void Beacon_control::CMD_MODE_ON(System::IO::Ports::SerialPort^ serialPort, char *type)
{
	unsigned char buff[100] = "PS0ONtC\r\n";
	int serialPort_out_length = 0;

	buff[5] = type[0];
	serialPort_out_length = strlen((char *)buff);
	serialPort_out(serialPort, buff, serialPort_out_length, 100);
}

void Beacon_control::CMD_MODE_OFF(System::IO::Ports::SerialPort^ serialPort)
{
	unsigned char buff[100] = "PS0OF0C\r\n";
	int serialPort_out_length = 0;

	serialPort_out_length = strlen((char *)buff);
	serialPort_out(serialPort, buff, serialPort_out_length, 100);
}

void Beacon_control::CMD_BLE_Scanner(System::IO::Ports::SerialPort^ serialPort, char CMD, unsigned char *Mac_Addr)
{
	unsigned char buff[100] = "PS2CMDc123456789ABCc\r\n";	//	총 22byte
	int length_cnt = 6;
	int serialPort_out_length = 0;

	serialPort_out_length = strlen((char *)buff);

	buff[length_cnt++] = CMD;


	for (int cnt = 0; cnt < 6; cnt++)
	{
		buff[length_cnt++] = Hex_to_ASC((Mac_Addr[cnt] >> 4) & 0x0f);
		buff[length_cnt++] = Hex_to_ASC(Mac_Addr[cnt] & 0x0f);
	}

	serialPort_out(serialPort, buff, serialPort_out_length, 100);
}

void Beacon_control::CMD_BLE_Scanner_Request(System::IO::Ports::SerialPort^ serialPort, char CMD, unsigned char *Mac_Addr)
{
	unsigned char buff[100] = "PS2REQc123456789ABCc\r\n";	//	
	int length_cnt = 6;
	int serialPort_out_length = 0;

	serialPort_out_length = strlen((char *)buff);

	buff[length_cnt++] = CMD;

	for (int cnt = 0; cnt < 6; cnt++)
	{
		buff[length_cnt++] = Hex_to_ASC((Mac_Addr[cnt] >> 4) & 0x0f);
		buff[length_cnt++] = Hex_to_ASC(Mac_Addr[cnt] & 0x0f);
	}

	serialPort_out(serialPort, buff, serialPort_out_length, 100);
}

void Beacon_control::CMD_BLE_MAC_Address_Setting(System::IO::Ports::SerialPort^ serialPort, unsigned char *Now_MacAddress, unsigned char *New_MacAddress)
{
	//PS1FFFFFFFFFFFFC20194000003cc$0d$0a
	unsigned char buff[100] = "PS1MAC123456789ABC123456789ABCc\r\n";	//	총 33byte
	int length_cnt = 6;
	int serialPort_out_length = 0;

	serialPort_out_length = strlen((char *)buff);

	for (int cnt = 0; cnt < 6; cnt++)
	{
		buff[length_cnt++] = Hex_to_ASC((Now_MacAddress[cnt] >> 4) & 0x0f);
		buff[length_cnt++] = Hex_to_ASC(Now_MacAddress[cnt] & 0x0f);
	}

	for (int cnt = 0; cnt < 6; cnt++)
	{
		buff[length_cnt++] = Hex_to_ASC((New_MacAddress[cnt] >> 4) & 0x0f);
		buff[length_cnt++] = Hex_to_ASC(New_MacAddress[cnt] & 0x0f);
	}

	serialPort_out(serialPort, buff, serialPort_out_length, 100);
}

void Beacon_control::CMD_BLE_MAC_Address_Setting_Request(System::IO::Ports::SerialPort^ serialPort, unsigned char *Now_MacAddress, unsigned char *New_MacAddress)
{
	unsigned char buff[100] = "PS1REQ123456789ABC123456789ABCc\r\n";
	int length_cnt = 6;
	int serialPort_out_length = 0;

	serialPort_out_length = strlen((char *)buff);

	for (int cnt = 0; cnt < 6; cnt++)
	{
		buff[length_cnt++] = Hex_to_ASC((Now_MacAddress[cnt] >> 4) & 0x0f);
		buff[length_cnt++] = Hex_to_ASC(Now_MacAddress[cnt] & 0x0f);
	}

	for (int cnt = 0; cnt < 6; cnt++)
	{
		buff[length_cnt++] = Hex_to_ASC((New_MacAddress[cnt] >> 4) & 0x0f);
		buff[length_cnt++] = Hex_to_ASC(New_MacAddress[cnt] & 0x0f);
	}

	serialPort_out(serialPort, buff, serialPort_out_length, 100);
}

void Beacon_control::serialPort_out(System::IO::Ports::SerialPort^  &serialPort, unsigned char *data, int length, int limit_buff_Max_byte)
{
	for (int cnt = 0; cnt < length; cnt++)
	{
		if (cnt >= limit_buff_Max_byte)
		{
			break;
		}
		else
		{
			serialPort->Write(To_String(data[cnt]));
		}
	}
}

void Beacon_control::dataGridView_ColorSet(System::Windows::Forms::DataGridView^  dataGridView, int Rows_Cnt, System::Drawing::Color ForeColor, System::Drawing::Color BackColor)
{
	dataGridView->Rows[Rows_Cnt]->DefaultCellStyle->ForeColor = ForeColor;
	dataGridView->Rows[Rows_Cnt]->DefaultCellStyle->BackColor = BackColor;
}


void Beacon_control::BLE_Scan_Mac_Address_Set_View_dataGridView(System::Windows::Forms::DataGridView^  dataGridView, BLE_SCAN_LIST *ListBefore, BLE_SCAN_LIST *ListAfter, System::Windows::Forms::Label^ list_Number, int View_Voltage)
{

	String ^ item_row = "";
	int Voltage = 0;
	int Complete_Quantity = 0;

	for (int Rows_Cnt = 0; Rows_Cnt < ListBefore->Registered_Quantity; Rows_Cnt++)
	{
		if (dataGridView->Rows->Count < ListBefore->Registered_Quantity + 1)
		{
			dataGridView->Rows->Add();
		}

		for (int Cells_Cnt = 0; Cells_Cnt < 6; Cells_Cnt++)
		{
			Voltage = ListAfter->data[Rows_Cnt].sub_data[0];
			if (ListAfter->data[Rows_Cnt].Command_processing_result == 1)
			{
				ListAfter->data[Rows_Cnt].Power_State = 0;
				ListAfter->data[Rows_Cnt].Command_processing_result = 0;
			}
			//	State 와 검사 결과에 따른 셀색 지정
			if (ListAfter->data[Rows_Cnt].Power_State == 0)
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::Black, System::Drawing::Color::SkyBlue);
			}
			else if (ListAfter->data[Rows_Cnt].sub_data[1] == 1)
			{
				dataGridView->Rows[Rows_Cnt]->Selected = 1;
				dataGridView->ClearSelection();

				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::White, System::Drawing::Color::Red);
			}
			else if (ListBefore->data[Rows_Cnt].State == 4)
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::White, System::Drawing::Color::OrangeRed);
			}
			else if (ListBefore->data[Rows_Cnt].State == 3)
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::Black, System::Drawing::Color::YellowGreen);
			}
			else
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::Black, System::Drawing::Color::Silver);
			}

			item_row = "";
			switch (Cells_Cnt)
			{
			case 0:	//	순서
				item_row = String::Format("{0}", Rows_Cnt);
				break;
			case 1:	//	MAC 주소 (변경 전)
				item_row = String::Format("[{0,2:X2}:{1,2:X2}:{2,2:X2}:{3,2:X2}:{4,2:X2}:{5,2:X2}]"
					, ListBefore->data[Rows_Cnt].mac.d8bit[5]
					, ListBefore->data[Rows_Cnt].mac.d8bit[4]
					, ListBefore->data[Rows_Cnt].mac.d8bit[3]
					, ListBefore->data[Rows_Cnt].mac.d8bit[2]
					, ListBefore->data[Rows_Cnt].mac.d8bit[1]
					, ListBefore->data[Rows_Cnt].mac.d8bit[0]
				);
				break;
			case 2:	//	MAC 주소 (변경 후)
				item_row = String::Format("[{0,2:X2}:{1,2:X2}:{2,2:X2}:{3,2:X2}:{4,2:X2}:{5,2:X2}]"
					, ListAfter->data[Rows_Cnt].mac.d8bit[5]
					, ListAfter->data[Rows_Cnt].mac.d8bit[4]
					, ListAfter->data[Rows_Cnt].mac.d8bit[3]
					, ListAfter->data[Rows_Cnt].mac.d8bit[2]
					, ListAfter->data[Rows_Cnt].mac.d8bit[1]
					, ListAfter->data[Rows_Cnt].mac.d8bit[0]
				);
				break;
			case 3:	//	배터리전압
				if (View_Voltage == 1)
				{
					item_row = String::Format("{0:f1}V", ((float)Voltage) / 10.0f);
				}
				else
				{
					item_row = "---";
				}
				break;
			case 4:	//	검사 상태

				switch (ListBefore->data[Rows_Cnt].State)
				{
				case 0:
					item_row = L"대기 중";
					break;
				case 3:
					item_row = L"설정 완료";
					break;
				case 4:
					item_row = L"배터리 교체 요망";
					break;
				default:
					item_row = L"설정 중";
					break;
				}
				break;
			case 5:
				switch (ListBefore->data[Rows_Cnt].State)
				{
				case 0:
					item_row = "";
					break;
				case 3:
					item_row = "";
					break;
				case 4:
					item_row = L"배터리 교체 후 재검사";
					break;
				default:
					item_row = "";
					break;
				}

				if (ListAfter->data[Rows_Cnt].sub_data[1] == 1)
				{
					item_row += L" [버튼 눌림]";
				}

				if (ListAfter->data[Rows_Cnt].Power_State == 0)
				{
					item_row += L" 전원 꺼짐";
				}

				break;

			}

			dataGridView->Rows[Rows_Cnt]->Cells[Cells_Cnt]->Value = item_row;
		}
	}

	if (BLE_Scanner.Mac_Address_setting.Select_index >= BLE_SCAN_LIST_MAX)
	{
		if (BLE_Scanner.Mac_Address_setting.Select_index_Before != BLE_Scanner.Mac_Address_setting.Select_index)
		{
			dataGridView->ClearSelection();
		}
	}

	if (ListBefore->Registered_Quantity == 0)
	{
		dataGridView->ClearSelection();
	}

	list_Number->Text = String::Format("{0,4}", BLE_Scanner.Mac_Address_setting.Complete_Quantity);

}

void Beacon_control::BLE_Scan_List_renewal_View_dataGridView_Clear(System::Windows::Forms::DataGridView^  dataGridView)
{
	dataGridView->Rows->Clear();
}

void Beacon_control::BLE_Scan_Hardware_Test_View_dataGridView(System::Windows::Forms::DataGridView^  dataGridView, BLE_SCAN_LIST *List, System::Windows::Forms::Label^ list_Number, int View_Voltage)
{

	SCAN_DATA read_data = { 0 };
	String ^ item_row = "";
	int Voltage = 0;
	int Complete_Quantity = 0;

	if (dataGridView->Rows->Count > List->Registered_Quantity)
	{
		dataGridView->Rows->Clear();
	}

	for (int Rows_Cnt = 0; Rows_Cnt < List->Registered_Quantity; Rows_Cnt++)
	{
		if (dataGridView->Rows->Count < List->Registered_Quantity)
		{
			dataGridView->Rows->Add();
		}

		for (int Cells_Cnt = 0; Cells_Cnt < 6; Cells_Cnt++)
		{
			Voltage = List->data[Rows_Cnt].sub_data[0];

			//	State 와 검사 결과에 따른 셀색 지정
			if (List->data[Rows_Cnt].State == 4)
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::White, System::Drawing::Color::OrangeRed);
			}
			else if (List->data[Rows_Cnt].State == 3)
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::Black, System::Drawing::Color::YellowGreen);
			}
			else
			{
				dataGridView_ColorSet(dataGridView, Rows_Cnt, System::Drawing::Color::Black, System::Drawing::Color::Silver);
			}

			item_row = "";
			switch (Cells_Cnt)
			{
			case 0:	//	순서
				item_row = String::Format("{0}", Rows_Cnt);
				break;
			case 1:	//	MAC 주소
//					item_row = String::Format("[{0,12:X12}]", List->data[Rows_Cnt].mac.d64bit);
				item_row = String::Format("[{0,2:X2}:{1,2:X2}:{2,2:X2}:{3,2:X2}:{4,2:X2}:{5,2:X2}]"
					, List->data[Rows_Cnt].mac.d8bit[5]
					, List->data[Rows_Cnt].mac.d8bit[4]
					, List->data[Rows_Cnt].mac.d8bit[3]
					, List->data[Rows_Cnt].mac.d8bit[2]
					, List->data[Rows_Cnt].mac.d8bit[1]
					, List->data[Rows_Cnt].mac.d8bit[0]
				);
				break;
			case 2:	//	수신감도
				item_row = String::Format("{0}dbm", (signed char)List->data[Rows_Cnt].sub_data[1]);
				break;
			case 3:	//	배터리전압
				if (View_Voltage == 1)
				{
					item_row = String::Format("{0:f1}V", ((float)Voltage) / 10.0f);
				}
				else
				{
					item_row = "---";
				}
				break;
			case 4:	//	검사 상태

				switch (List->data[Rows_Cnt].State)
				{
				case 0:
					item_row = L"대기 중";
					break;
				case 3:
					item_row = L"정상 품";
					break;
				case 4:
					item_row = L"재검사 요망";
					break;
				default:
					item_row = L"검사 중";
					break;
				}
				break;
			case 5:
				switch (List->data[Rows_Cnt].State)
				{
				case 0:
					item_row = "";
					break;
				case 3:
					item_row = "";
					break;
				case 4:
					item_row = L"배터리 교체 후 재검사";
					break;
				default:
					item_row = "";
					break;
				}
				break;

			}

			if ((Rows_Cnt == 0) && (Cells_Cnt == 2))
			{
				//					dataGridView->Rows[Rows_Cnt]->Cells[Cells_Cnt]->Style->ForeColor = System::Drawing::Color::Red;
				//					dataGridView->Rows[Rows_Cnt]->Cells[Cells_Cnt]->Style->BackColor = System::Drawing::Color::Green;
			}


			dataGridView->Rows[Rows_Cnt]->Cells[Cells_Cnt]->Value = item_row;
		}
	}

	dataGridView->ClearSelection();

	list_Number->Text = String::Format("{0,4}", BLE_Scanner.Hardware_test.Complete_Quantity);

}

void Beacon_control::serial_data_Decoder_init()
{
	strncpy_s((char *)serialPort1_decoder.receive[0].start_signature, 20, "CMD", 3);
	serialPort1_decoder.receive[0].start_signature_length = 3;
	serialPort1_decoder.receive[0].start_signature_check_position = 0;

	strncpy_s((char *)serialPort1_decoder.receive[0].end_signature, 20, "\r", 1);
	serialPort1_decoder.receive[0].end_signature_length = 1;
	serialPort1_decoder.receive[0].end_signature_check_position = 0;
}

void Beacon_control::serial_data_Decoder(SERIAL_DECODER_TYPE *serialPort_decoder, unsigned char data)
{
	for (int decoder_index = 0; decoder_index < SERIAL1_DATA_TYPE_MAX; decoder_index++)
	{
		switch (serialPort_decoder->sequence)
		{
		case SERIAL_SEQUENCE_START_CHECK:
			if (data == serialPort_decoder->receive[decoder_index].start_signature[serialPort_decoder->receive[decoder_index].start_signature_check_position])
			{
				if (++serialPort_decoder->receive[decoder_index].start_signature_check_position >= serialPort_decoder->receive[decoder_index].start_signature_length)
				{
					serialPort_decoder->sequence = SERIAL_SEQUENCE_END_CHECK;
					serialPort_decoder->receive[decoder_index].start_signature_check_position = 0;
					serialPort_decoder->receive[decoder_index].end_signature_check_position = 0;
					serialPort_decoder->receive[decoder_index].data_cnt = 0;
				}

			}
			else
			{
				serialPort_decoder->receive[decoder_index].start_signature_check_position = 0;
				serialPort_decoder->receive[decoder_index].end_signature_check_position = 0;
				serialPort_decoder->receive[decoder_index].data_cnt = 0;
			}
			break;
		case SERIAL_SEQUENCE_END_CHECK:

			serialPort_decoder_DataCopy(serialPort_decoder, decoder_index, data);

			if (data == serialPort_decoder->receive[decoder_index].end_signature[serialPort_decoder->receive[decoder_index].end_signature_check_position])
			{
				if (++serialPort_decoder->receive[decoder_index].end_signature_check_position >= serialPort_decoder->receive[decoder_index].end_signature_length)
				{
					serialPort_decoder_Execution(decoder_index, serialPort_decoder->receive[decoder_index].data);
					serialPort_decoder->sequence = SERIAL_SEQUENCE_START_CHECK;
					serialPort_decoder->receive[decoder_index].end_signature_check_position = 0;
				}
			}
			break;
		default:
			break;
		}
	}
}

void Beacon_control::serialPort_decoder_DataCopy(SERIAL_DECODER_TYPE *serialPort_decoder, int index, unsigned char data)
{
	serialPort_decoder->receive[index].data[serialPort_decoder->receive[index].data_cnt++] = data;
	if (serialPort_decoder->receive[index].data_cnt >= SERIAL_RECEIVE_BUFF_MAX)
	{
		serialPort_decoder->receive[index].data_cnt = 0;
	}
}


void Beacon_control::Beacon_control_Timer_Process(System::IO::Ports::SerialPort^  serialPort, System::Windows::Forms::TextBox^  Next_MAC_num_textBox, System::Windows::Forms::TextBox^  Month_textBox)
{
		unsigned char read_Data = 0;
		if (Uart_rx_Time_Out >= 100)
		{
			Uart_rx_Time_Out = 0;
			while (Uart_Q_pop(&Uart1, &read_Data) == TRUE)
			{
				BLE_Data_Read(read_Data);
				BLE_CMD_Read(read_Data);
				serial_data_Decoder(&serialPort1_decoder, read_Data);

				WriteCnt++;
			}

			BLE_CMD_Tick_isr(serialPort);
			Uart_rx_Time_Out_Cnt++;
		}

		BLE_CMD_Auto_isr();
		BLE_MAC_Address_Setting_Process(Next_MAC_num_textBox, Month_textBox);
		BLE_All_Auto_Process();
		BLE_List_Cmd_Process();
}

Beacon_control::Beacon_control()
{
	this->BLE_Scanner_connection = 0;
	this->hardware_test_complete = 0;
	this->BLE_MAC_Address_Setting_Auto_Process = 0;
	this->Hardware_test_Allowable_voltage = 30;	//	허용 배터리 전압

	excel_file_Constructor();
}

int Beacon_control::Get_BLE_Scanner_connection()
{
	return (this->BLE_Scanner_connection);
}

void Beacon_control::Set_BLE_Scanner_connection()
{
	this->BLE_Scanner_connection = 1;
}

void Beacon_control::Clr_BLE_Scanner_connection()
{
	this->BLE_Scanner_connection = 0;
}

int Beacon_control::Get_hardware_test_complete()
{
	return (this->hardware_test_complete);
}

void Beacon_control::Clr_hardware_test_complete()
{
	this->hardware_test_complete = 0;
}

void Beacon_control::Set_BLE_MAC_Address_Setting_Auto_Process()
{
	this->BLE_MAC_Address_Setting_Auto_Process = 1;
}
void Beacon_control::Clr_BLE_MAC_Address_Setting_Auto_Process()
{
	this->BLE_MAC_Address_Setting_Auto_Process = 0;
}
int Beacon_control::Get_BLE_MAC_Address_Setting_Auto_Process()
{
	return (this->BLE_MAC_Address_Setting_Auto_Process);
}

void Beacon_control::Set_Hardware_test_Allowable_voltage(unsigned char voltage)
{
	this->Hardware_test_Allowable_voltage = voltage;
}
unsigned char Beacon_control::Get_Hardware_test_Allowable_voltage()
{
	return (this->Hardware_test_Allowable_voltage);
}

Beacon_control::~Beacon_control()
{
}
