#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <tchar.h>
#include <atlstr.h>
#include <iostream>
#include <sstream>

ref class vc_lib
{
public:
	vc_lib();
	///////////////////////////////////////////////////////////////////////
	// ANSI char* 에서 UFT8 로의 형변환 함수
	char*		ANSItoUTF8(char* pszCode);
	///////////////////////////////////////////////////////////////////////
	// UTF8 에서 ANSI char* 로의 형변환 함수
	char*		UTF8toANSI(char* pszCode);
	///////////////////////////////////////////////////////////////////////
	//wchar_t 에서 char 로의 형변환 함수
	char *		ConvertWCtoC(wchar_t* str);
	///////////////////////////////////////////////////////////////////////
	//char 에서 wchar_t 로의 형변환 함수
	wchar_t*	ConverCtoWC(char* str);
	///////////////////////////////////////////////////////////////////////
	// System::String^ 에서 char* 로의 형변환 함수
	// 입력 인자 : System::String ^ in_String
	// 출력 인자 : char *char_buff, int char_buff_size
	void		To_Char(System::String ^ in_String, char *char_buff, int char_buff_size);
	///////////////////////////////////////////////////////////////////////
	// std::string 에서 char 로의 형변환 함수
	void To_Char(std::string input, char* output, int output_length);

	///////////////////////////////////////////////////////////////////////
	// char* 에서 System::String^ 로의 형변환 함수
	System::String^	To_String(char *in_char);
	///////////////////////////////////////////////////////////////////////
	// char 1byte 에서 System::String^ 로의 형변환 함수
	System::String^ To_String(char in_char);
	///////////////////////////////////////////////////////////////////////
	// std::string 에서 System::String^ 로의 형변환 함수
	System::String ^ To_String(std::string input);

	///////////////////////////////////////////////////////////////////////
	// char *data 에서 int 로의 형변환 함수
	int To_int(char* in_data);
	///////////////////////////////////////////////////////////////////////
	// std::string 에서 int 로의 형변환 함수
	int To_int(std::string in_data);
	///////////////////////////////////////////////////////////////////////
	// data1내용과 data2내용을 비교 후 결과를 return 한다. 
	// 결과 0: 일치, 1: 불일치
	int Data_Cmp(char *data1, char *data2, int length);
	///////////////////////////////////////////////////////////////////////
	// Hex =>> ASC code 
	char Hex_to_ASC(unsigned char data);
	///////////////////////////////////////////////////////////////////////
	// ASC code =>> Hex 
	char ASC_to_Hex(char str);
	///////////////////////////////////////////////////////////////////////
	// 현재 날짜 및 시간 등을 취한다.
	// String ^format : YYYY-MM-DD.hh:mm:ss => 2019-12-3.18:02:24
	// "yyyy년MMMMdd일 dddd hh시mm분ss초"=> 2019년 12월03일 화요일 06시12분24초
	System::String ^ vc_lib::date_Read(System::String ^format);

	virtual ~vc_lib();
};

