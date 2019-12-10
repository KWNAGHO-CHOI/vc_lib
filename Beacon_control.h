#pragma once

#include <stdio.h>
#include <atlstr.h>
#include "vc_lib.h"
#include "excel_file_system.h"
#include "ini_file_system.h"

// excel file color code
// excel file color code
#define TITLE_BG_COLOR_MAC_SET_REPORT "0093c47d"
#define LOGO_FONT_COLOR_MAC_SET_REPORT "006aa84f"
#define	TITLE_FONT_COLOR	"00a64c0e"
#define	LOGO_FONT_COLOR		"00ed7d31"
#define	TITLE_BG_COLOR		"00f8cbad"
#define	NORMAL_BG_COLOR		"00ffffff"
#define SIDE_LIMIT_SELL_BG_COLOR	"0x00808080"
// excel file color code
// excel file color code


#define	CMD_POWER_OFF	'0'
#define	CMD_LED_ON		'1'
#define	CMD_LED_OFF		'2'

#define BLE_SCAN_LIST_OFF_SET_NORMAL		0		//	~ 199
#define BLE_SCAN_LIST_OFF_SET_CONITE		200		//	~ 399
#define BLE_SCAN_LIST_OFF_SET_MANUFACTURE	400		//	~ 599
#define BLE_SCAN_LIST_OFF_SET_OTHER			600		//	~ 799

#define BLE_SCAN_LIST_QUEUE_MAX		200
#define SERIAL_RECEIVE_BUFF_MAX		100
#define	RESTART_TIME	40

typedef union __scan_mac_addr_data {
	unsigned __int64 d64bit;
	struct {
		unsigned char d8bit[8];
	};
}SCAN_MAC_ADDR_DATA;

typedef struct __scan_data {
	SCAN_MAC_ADDR_DATA mac;
	unsigned char sub_data[2];
	int State;
	int Power_State;
	int Command_processing_result;
}SCAN_DATA;
typedef	struct __scan_list_queue {
	int head;
	int tail;
	SCAN_DATA data[BLE_SCAN_LIST_QUEUE_MAX];
	int overflow_cnt;
	int overflow_err;
}SCAN_LIST_QUEUE;

#define	UART_DATA_QUEUE_MAX		1000
typedef struct __uart_data_queue {
	int head;
	int tail;
	unsigned char data[UART_DATA_QUEUE_MAX];
}UART_DATA_QUEUE;

#define BLE_SCAN_LIST_MAX	10000
typedef struct __ble_scan_list {
	SCAN_DATA data[BLE_SCAN_LIST_MAX];
	int cnt;
	int Registered_Quantity;
	int Registered_Quantity_Before;
	int cmd_now_index;
	int Target_index;
	int Select_index;
}BLE_SCAN_LIST;

enum __BLE_SCANNER_LIST_ENUM
{
	BLE_SCANNER_LIST_NORMAL = 0
	, BLE_SCANNER_LIST_CONITE
	, BLE_SCANNER_LIST_MANUFACTURE
	, BLE_SCANNER_LIST_MAC_ADDR_SET
	, BLE_SCANNER_LIST_OTHER
	, BLE_SCANNER_LIST_KC_1
	, BLE_SCANNER_LIST_KC_2
	//===============================
	, BLE_SCANNER_LIST_MAX
};

typedef struct __ble_scan_hardware_test {
	int Inspection_Quantity;			//	검사 수량 카운터
	int Re_inspection_Quantity;			//	재 검사 수량 카운터
	int Complete_Quantity;				//	검사 완료 수량 누적 카운터
	int Complete_Quantity_now;			//	현재 검사 완료 수량 카운터
	int Defect_Product_Quantity;		//	결함 제품 누적 카운터
	int Defect_Product_Quantity_now;	//	현재 결함 제품 카운터
}BLE_SCAN_HW_TEST;

typedef struct __ble_scan_mac_address_setting {
	int Mac_setting_flag;	//	MAC 주소 설정
	int Complete_Quantity;	//	MAC 주소 설정 완료 수량 누적 카운터
	int Complete_Quantity_now;			//	현재 검사 완료 수량 카운터
	int Select_index;
	int Select_index_Before;
}BLE_SCAN_MAC_SET;


typedef struct __ble_scan_normal_admin_control {
	int Select_index;
	int Select_index_time_out;
}BLE_SCAN_NORMAL_ADMIN_CTL;

typedef struct __ble_scan_list_cmd_control {
	BLE_SCAN_LIST fixing;
	BLE_SCAN_LIST Before;
	BLE_SCAN_LIST After;
	int Delay;
	int Seq;
	int cmd_Enable_flag;
	int CMD;
}BLE_SCN_LIST_CMD_CTL;

typedef struct __control_variable
{
	BLE_SCAN_HW_TEST Hardware_test;
	BLE_SCAN_MAC_SET Mac_Address_setting;
	BLE_SCAN_NORMAL_ADMIN_CTL Normal_Admin;
	BLE_SCN_LIST_CMD_CTL list;
	int *Command_processing_result;
	unsigned char copyBuff[100];
	int copyBuff_Cnt;
}CONTROL_VARIABLE;

typedef struct __serial_receive_str {
	unsigned char data[SERIAL_RECEIVE_BUFF_MAX];
	unsigned char start_signature[20];
	unsigned char end_signature[20];
	int start_signature_length;
	int end_signature_length;
	int start_signature_check_position;
	int end_signature_check_position;
	int data_cnt;
}SERIAL_RECEIVE_STR;

enum __SERIAL1_DATA_TYPE_ENUM
{
	SERIAL1_DATA_TYPE_CMD_0 = 0
	//===============================
	, SERIAL1_DATA_TYPE_MAX
};

enum __SERIAL_SEQUENCE_ENUM
{
	SERIAL_SEQUENCE_START_CHECK = 0
	, SERIAL_SEQUENCE_END_CHECK
	//===============================
	, SERIAL_SEQUENCE_MAX
};

typedef struct __serial_decoder_type {
	SERIAL_RECEIVE_STR receive[SERIAL1_DATA_TYPE_MAX];
	int sequence;
}SERIAL_DECODER_TYPE;

extern CONTROL_VARIABLE BLE_Scanner;
extern BLE_SCAN_LIST BLE_Scanner_list[BLE_SCANNER_LIST_MAX];

using namespace System;

ref class Beacon_control : public vc_lib
{
private: excel_file_system excel;
		 ini_file_system ini_lib;

public:
	int BLE_Scanner_connection;
	int hardware_test_complete;
	int BLE_MAC_Address_Setting_Auto_Process;
	int Beacon_Hardware_test_Report_Print_State;
	unsigned char Hardware_test_Allowable_voltage;	//	허용 배터리 전압
public:
	Beacon_control();

	int Get_BLE_Scanner_connection();
	void Set_BLE_Scanner_connection();
	void Clr_BLE_Scanner_connection();

	int Get_hardware_test_complete();
	void Clr_hardware_test_complete();
	void Set_BLE_MAC_Address_Setting_Auto_Process();
	void Clr_BLE_MAC_Address_Setting_Auto_Process();
	int Get_BLE_MAC_Address_Setting_Auto_Process();
	void Set_Hardware_test_Allowable_voltage(unsigned char voltage);
	unsigned char Get_Hardware_test_Allowable_voltage();

	void excel_file_handle_setting(EXCEL_FILE_HANDLE_TYPE &excel_file_handle);
	void excel_file_Constructor();
	void excel_file_open_and_load(EXCEL_FILE_HANDLE_TYPE& excel_file_handle, xlnt::workbook& wb, xlnt::worksheet& ws, std::string& filename);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 기존 기록된 파일일 경우 이어서 쓸지점을 검색하는 함수
	void excel_now_row_Search(xlnt::worksheet& ws, EXCEL_FILE_HANDLE_TYPE& excel_file_handle, xlnt::column_t column, char* title_Signature);

	void excel_Hardware_Test_Report(SCAN_DATA outlist_data, EXCEL_FILE_HANDLE_TYPE& excel_file_handle);
	void excel_HW_Test_Report_Header_write(xlnt::worksheet& ws, xlnt::workbook& wb, EXCEL_FILE_HANDLE_TYPE& excel_file_handle);
	void excel_HW_Test_Report_list_write(xlnt::worksheet& ws, xlnt::workbook& wb, SCAN_DATA outlist_data, EXCEL_FILE_HANDLE_TYPE& excel_file_handle);

	void excel_MAC_Address_Allocation_Report(SCAN_DATA ListBefore, SCAN_DATA ListAfter, EXCEL_FILE_HANDLE_TYPE& excel_file_handle);
	void excel_MAC_Address_Allocation_Report_Header_write(xlnt::worksheet& ws, xlnt::workbook& wb, EXCEL_FILE_HANDLE_TYPE& excel_file_handle);
	void excel_MAC_Address_Allocation_Report_list_write(xlnt::worksheet& ws, xlnt::workbook& wb, SCAN_DATA ListBefore, SCAN_DATA ListAfter, EXCEL_FILE_HANDLE_TYPE& excel_file_handle);

	void BLE_Scan_List_renewal_View_dataGridView_Clear(System::Windows::Forms::DataGridView^  dataGridView);
	void BLE_Scan_Hardware_Test_View_dataGridView(System::Windows::Forms::DataGridView^  dataGridView, BLE_SCAN_LIST *List, System::Windows::Forms::Label^ list_Number, int View_Voltage);
	void dataGridView_ColorSet(System::Windows::Forms::DataGridView^  dataGridView, int Rows_Cnt, System::Drawing::Color ForeColor, System::Drawing::Color BackColor);
	void BLE_Scan_Mac_Address_Set_View_dataGridView(System::Windows::Forms::DataGridView^  dataGridView, BLE_SCAN_LIST *ListBefore, BLE_SCAN_LIST *ListAfter, System::Windows::Forms::Label^ list_Number, int View_Voltage);

	void serial_data_Decoder_init();
	void serial_data_Decoder(SERIAL_DECODER_TYPE *serialPort_decoder, unsigned char data);

	void BLE_List_Cmd_Process_init();
	void BLE_List_Cmd_Process_Clear();
	int BLE_list_Registeri_Check(SCAN_MAC_ADDR_DATA *Check_mac, BLE_SCAN_LIST *List);
	int BLE_list_Registeri_Index_Read(SCAN_MAC_ADDR_DATA *Check_mac, BLE_SCAN_LIST *List);
	void BLE_All_Auto_Process();
	int BLE_List_RemoveAt(BLE_SCAN_LIST *List, int Index);
	void BLE_MAC_Address_Set_Enable(unsigned char *Addr_Now, unsigned char *Addr_New);
	void BLE_List_Cmd_Fixing_Reload(BLE_SCAN_LIST *List);
	void BLE_Scan_Hardware_Test_View_init(void);
	void BLE_ALL_Auto_Process_init();
	void BLE_List_Cmd_Process();
	void BLE_MAC_Address_Setting_Process(System::Windows::Forms::TextBox^  Next_MAC_num_textBox, System::Windows::Forms::TextBox^  Month_textBox);
	void BLE_Data_Read(unsigned char data);
	void BLE_CMD_Read(unsigned char data);
	void BLE_CMD_RxReq_Check(unsigned char data);
	void BLE_CMD_TxSeq_Check(unsigned char data);

	void BLE_CMD_Tick_isr(System::IO::Ports::SerialPort^  serialPort);
	void BLE_CMD_Auto_isr();
	void Uart_tickISR();

	void serialPort_decoder_Execution(int index, unsigned char *Check_Buff);
	void Qpush_serial_1_Rx_Buffer(System::IO::Ports::SerialPort^ serialPort);
	void Beacon_control_Timer_Process(System::IO::Ports::SerialPort^  serialPort, System::Windows::Forms::TextBox^  Next_MAC_num_textBox, System::Windows::Forms::TextBox^  Month_textBox);
	int BLE_CMD_TxStart(int CMD);
	void BLE_CMD_TxStart_Erase();
	void BLE_CMD_TxRestart();
	int BLE_MAC_Address_Setting_TxStart();
	void BLE_MAC_Address_Setting_TxRestart();
	void BLE_CMD_Mac_Addr_Set(unsigned char *Mac_Addr);
	void CMD_MODE_ON(System::IO::Ports::SerialPort^ serialPort, char *type);
	void CMD_MODE_OFF(System::IO::Ports::SerialPort^ serialPort);
	void CMD_BLE_Scanner(System::IO::Ports::SerialPort^ serialPort, char CMD, unsigned char *Mac_Addr);
	void CMD_BLE_Scanner_Request(System::IO::Ports::SerialPort^ serialPort, char CMD, unsigned char *Mac_Addr);
	void CMD_BLE_MAC_Address_Setting(System::IO::Ports::SerialPort^ serialPort, unsigned char *Now_MacAddress, unsigned char *New_MacAddress);
	void CMD_BLE_MAC_Address_Setting_Request(System::IO::Ports::SerialPort^ serialPort, unsigned char *Now_MacAddress, unsigned char *New_MacAddress);
	void serialPort_out(System::IO::Ports::SerialPort^  &serialPort, unsigned char *data, int length, int limit_buff_Max_byte);
	void serialPort_decoder_DataCopy(SERIAL_DECODER_TYPE *serialPort_decoder, int index, unsigned char data);

	virtual ~Beacon_control();
};

