#pragma once

#include <stdio.h>
#include <atlstr.h>
#include "vc_lib.h"

ref class ini_file_system : public vc_lib
{
public:
	ini_file_system();
	void write_INI_Value(char* lpAppName, char* lpKeyName, char* lpString, LPCTSTR lpFileName);
	void write_INI_Value(char* lpAppName, char* lpKeyName, System::String^ lpString, LPCTSTR lpFileName);
	void write_INI_Value(char* lpAppName, char* lpKeyName, CString lpString, LPCTSTR lpFileName);
	void read_INI_Value(System::String^ &str, char * lpAppName, char * lpKeyName, char * lpDefault, DWORD nSize, LPCTSTR lpFileName);

	virtual ~ini_file_system();
};

