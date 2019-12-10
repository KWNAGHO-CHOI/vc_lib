#include "ini_file_system.h"

ini_file_system::ini_file_system()
{
}


ini_file_system::~ini_file_system()
{
}

void ini_file_system::write_INI_Value(char* lpAppName, char* lpKeyName, char* lpString, LPCTSTR lpFileName)
{
	CString strSection = To_String(lpAppName);
	CString strKey = To_String(lpKeyName);
	CString strString = To_String(lpString);

	WritePrivateProfileString(strSection, strKey, strString, lpFileName);
}

void ini_file_system::write_INI_Value(char* lpAppName, char* lpKeyName, System::String ^ lpString, LPCTSTR lpFileName)
{
	CString strSection = To_String(lpAppName);
	CString strKey = To_String(lpKeyName);
	CString strString(lpString);

	WritePrivateProfileString(strSection, strKey, strString, lpFileName);
}

void ini_file_system::write_INI_Value(char* lpAppName, char* lpKeyName, CString lpString, LPCTSTR lpFileName)
{
	CString strSection = To_String(lpAppName);
	CString strKey = To_String(lpKeyName);
	CString strString(lpString);

	WritePrivateProfileString(strSection, strKey, strString, lpFileName);
}

void ini_file_system::read_INI_Value(System::String^ &str, char *lpAppName, char *lpKeyName, char *lpDefault, DWORD nSize, LPCTSTR lpFileName)
{
	wchar_t szBuf[100];
	CString strSection = To_String(lpAppName);
	CString strKey = To_String(lpKeyName);
	CString strDefault = To_String(lpDefault);

	int sizeGetchar = GetPrivateProfileString(strSection, strKey, strDefault, szBuf, 8, lpFileName);
	for (int cnt = 0; cnt < sizeGetchar; cnt++)
	{
		str += szBuf[cnt];
	}
}
