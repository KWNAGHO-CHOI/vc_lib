#include "vc_lib.h"



vc_lib::vc_lib()
{
}


vc_lib::~vc_lib()
{
}

LPWSTR	AnsiToUnicode(LPWSTR unicode, LPSTR ansi)
{
	MultiByteToWideChar(CP_ACP, 0, ansi, -1, unicode, sizeof(unicode));				// ��Ȯ��
	return unicode;
}

LPSTR	UnicodeToAnsi(LPSTR ansi, LPCWSTR unicode)
{
	WideCharToMultiByte(CP_ACP, 0, unicode, -1, ansi, wcslen(unicode) * 2, NULL, NULL);
	return ansi;
}

LPSTR	UnicodeToUtf8(LPSTR &utf8, LPCWSTR unicode)
{
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, sizeof(utf8), NULL, NULL);	// ��Ȯ��
	return utf8;
}

LPWSTR	Utf8ToUnicode(LPWSTR unicode, LPCSTR utf8)
{
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, unicode, strlen(utf8) * 2);				// ��Ȯ��
	return unicode;
}

///////////////////////////////////////////////////////////////////////
// ANSI char* ���� UFT8 ���� ����ȯ �Լ�
char* vc_lib::ANSItoUTF8(char* pszCode)
{
	BSTR bstrCode;
	char* pszUTFCode = NULL;
	int  nLength, nLength2;

	nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), NULL, NULL);
	bstrCode = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), bstrCode, nLength);

	nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL);
	pszUTFCode = (char*)malloc(nLength2 + 1);
	WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL);

	return pszUTFCode;
}

///////////////////////////////////////////////////////////////////////
// UTF8 ���� ANSI char* ���� ����ȯ �Լ�
char* vc_lib::UTF8toANSI(char* pszCode)
{
	BSTR    bstrWide;
	char*   pszAnsi = NULL;
	int     nLength;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_UTF8, 0, pszCode, strlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
}

///////////////////////////////////////////////////////////////////////
//wchar_t ���� char ���� ����ȯ �Լ�
char * vc_lib::ConvertWCtoC(wchar_t* str)
{
	//��ȯ�� char* ���� ����
	char* pStr;

	//�Է¹��� wchar_t ������ ���̸� ����
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* �޸� �Ҵ�
	pStr = new char[strSize];

	//�� ��ȯ
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}

///////////////////////////////////////////////////////////////////////
//char ���� wchar_t ���� ����ȯ �Լ�
wchar_t* vc_lib::ConverCtoWC(char* str)
{
	//wchar_t�� ���� ����
	wchar_t* pStr;
	//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	//wchar_t �޸� �Ҵ�
	pStr = new WCHAR[strSize];
	//�� ��ȯ
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

	return pStr;
}

///////////////////////////////////////////////////////////////////////
// System::String^ ���� char* ���� ����ȯ �Լ�
// �Է� ���� : System::String ^ in_String
// ��� ���� : char *char_buff, int char_buff_size
void vc_lib::To_Char(System::String ^ in_String, char *char_buff, int char_buff_size)
{
	int strlenth = in_String->Length;
	wchar_t buff[100];

	for (int cnt = 0; cnt < strlenth; cnt++)
	{
		buff[cnt] = in_String[cnt];
	}

	strcpy_s(char_buff, char_buff_size, ConvertWCtoC(buff));
}

///////////////////////////////////////////////////////////////////////
// std::string ���� char ���� ����ȯ �Լ�
void vc_lib::To_Char(std::string input, char* output, int output_length)
{
	sprintf_s(output, output_length, "%s", input.c_str());
}


///////////////////////////////////////////////////////////////////////
// char* ���� System::String^ ���� ����ȯ �Լ�
System::String ^ vc_lib::To_String(char *in_char)
{
	int strlenth = strlen(in_char);
	wchar_t *buff = ConverCtoWC(in_char);
	System::String ^ outString;
	

	for (int cnt = 0; cnt < strlenth; cnt++)
	{
		outString += buff[cnt];
	}

	return (outString);
}

///////////////////////////////////////////////////////////////////////
// char 1byte ���� System::String^ ���� ����ȯ �Լ�
System::String ^ vc_lib::To_String(char in_char)
{
	char temp[2] = {in_char,0};
	wchar_t *buff = ConverCtoWC(temp);
	System::String ^ outString;

	outString += buff[0];

	return (outString);
}

///////////////////////////////////////////////////////////////////////
// std::string ���� System::String^ ���� ����ȯ �Լ�
System::String ^ vc_lib::To_String(std::string input)
{
	char temp[100];
	To_Char(input, temp, 100);

	return (To_String(temp));
}

///////////////////////////////////////////////////////////////////////
// char *data ���� int ���� ����ȯ �Լ�
int vc_lib::To_int(char* in_data)
{
	int out_int = 0;

	std::stringstream ss(in_data);
	ss >> out_int;
	if ((ss >> out_int).fail())
	{
		/* ���� */
	}
	return (out_int);
}

///////////////////////////////////////////////////////////////////////
// std::string ���� int ���� ����ȯ �Լ�
int vc_lib::To_int(std::string in_data)
{
	char data[100];
	To_Char(in_data, data, 100);

	return (To_int(data));

}


///////////////////////////////////////////////////////////////////////
// data1����� data2������ �� �� ����� return �Ѵ�. 
// ��� 0: ��ġ, 1: ����ġ
int vc_lib::Data_Cmp(char *data1, char *data2, int length)
{
	int result = 0;

	while (length--)
	{
		if (*data1++ != *data2++)
		{
			result = 1;
			break;
		}
	}

	return (result);
}


///////////////////////////////////////////////////////////////////////
// Hex =>> ASC code 
char vc_lib::Hex_to_ASC(unsigned char data)
{
	switch (data)
	{
	case 0:return ('0');
	case 1:return ('1');
	case 2:return ('2');
	case 3:return ('3');
	case 4:return ('4');
	case 5:return ('5');
	case 6:return ('6');
	case 7:return ('7');
	case 8:return ('8');
	case 9:return ('9');
	case 10:return ('A');
	case 11:return ('B');
	case 12:return ('C');
	case 13:return ('D');
	case 14:return ('E');
	case 15:return ('F');

	}
	return (0);
}

///////////////////////////////////////////////////////////////////////
// ASC code =>> Hex 
char vc_lib::ASC_to_Hex(char str)
{
	switch (str)
	{
	case '0':return (0x00);
	case '1':return (0x01);
	case '2':return (0x02);
	case '3':return (0x03);
	case '4':return (0x04);
	case '5':return (0x05);
	case '6':return (0x06);
	case '7':return (0x07);
	case '8':return (0x08);
	case '9':return (0x09);
	case 'A':case 'a':return (0x0A);
	case 'B':case 'b':return (0x0B);
	case 'C':case 'c':return (0x0C);
	case 'D':case 'd':return (0x0D);
	case 'E':case 'e':return (0x0E);
	case 'F':case 'f':return (0x0F);
	}
	return (0x00);
}

///////////////////////////////////////////////////////////////////////
// ���� ��¥ �� �ð� ���� ���Ѵ�.
// String ^format : YYYY-MM-DD.hh:mm:ss => 2019-12-3.18:02:24
// "yyyy��MMMMdd�� dddd hh��mm��ss��"=> 2019�� 12��03�� ȭ���� 06��12��24��
System::String ^ vc_lib::date_Read(System::String ^format)
{
	System::String ^result = System::DateTime().Now.ToString(format);
	return (result);
}
