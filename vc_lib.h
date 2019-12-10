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
	// ANSI char* ���� UFT8 ���� ����ȯ �Լ�
	char*		ANSItoUTF8(char* pszCode);
	///////////////////////////////////////////////////////////////////////
	// UTF8 ���� ANSI char* ���� ����ȯ �Լ�
	char*		UTF8toANSI(char* pszCode);
	///////////////////////////////////////////////////////////////////////
	//wchar_t ���� char ���� ����ȯ �Լ�
	char *		ConvertWCtoC(wchar_t* str);
	///////////////////////////////////////////////////////////////////////
	//char ���� wchar_t ���� ����ȯ �Լ�
	wchar_t*	ConverCtoWC(char* str);
	///////////////////////////////////////////////////////////////////////
	// System::String^ ���� char* ���� ����ȯ �Լ�
	// �Է� ���� : System::String ^ in_String
	// ��� ���� : char *char_buff, int char_buff_size
	void		To_Char(System::String ^ in_String, char *char_buff, int char_buff_size);
	///////////////////////////////////////////////////////////////////////
	// std::string ���� char ���� ����ȯ �Լ�
	void To_Char(std::string input, char* output, int output_length);

	///////////////////////////////////////////////////////////////////////
	// char* ���� System::String^ ���� ����ȯ �Լ�
	System::String^	To_String(char *in_char);
	///////////////////////////////////////////////////////////////////////
	// char 1byte ���� System::String^ ���� ����ȯ �Լ�
	System::String^ To_String(char in_char);
	///////////////////////////////////////////////////////////////////////
	// std::string ���� System::String^ ���� ����ȯ �Լ�
	System::String ^ To_String(std::string input);

	///////////////////////////////////////////////////////////////////////
	// char *data ���� int ���� ����ȯ �Լ�
	int To_int(char* in_data);
	///////////////////////////////////////////////////////////////////////
	// std::string ���� int ���� ����ȯ �Լ�
	int To_int(std::string in_data);
	///////////////////////////////////////////////////////////////////////
	// data1����� data2������ �� �� ����� return �Ѵ�. 
	// ��� 0: ��ġ, 1: ����ġ
	int Data_Cmp(char *data1, char *data2, int length);
	///////////////////////////////////////////////////////////////////////
	// Hex =>> ASC code 
	char Hex_to_ASC(unsigned char data);
	///////////////////////////////////////////////////////////////////////
	// ASC code =>> Hex 
	char ASC_to_Hex(char str);
	///////////////////////////////////////////////////////////////////////
	// ���� ��¥ �� �ð� ���� ���Ѵ�.
	// String ^format : YYYY-MM-DD.hh:mm:ss => 2019-12-3.18:02:24
	// "yyyy��MMMMdd�� dddd hh��mm��ss��"=> 2019�� 12��03�� ȭ���� 06��12��24��
	System::String ^ vc_lib::date_Read(System::String ^format);

	virtual ~vc_lib();
};

