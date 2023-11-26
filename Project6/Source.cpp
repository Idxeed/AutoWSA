#include <iostream>
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <codecvt>

#include "Header.h"
#include "Graph.h"


#define ENV_VAR_STRING_COUNT  (sizeof(envVarStrings)/sizeof(TCHAR*))
#define INFO_BUFFER_SIZE 32767

#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif


using namespace std; 

TCHAR* ConvSTRtoTCHAR(string s)
{
	TCHAR* b = 0;
	b = new TCHAR[s.size() + 1];
	copy(s.begin(), s.end(), b);
	b[s.size()] = 0;
	return b;
}

string ConvTCHARtoSTR(TCHAR* T)
{
	wchar_t* arr = T;
	basic_string<TCHAR> stri = arr;
	wstring ws(stri);
	string str(ws.begin(), ws.end());
	return str;
}

string GetUserNameQ()
{
	DWORD bufCharCount = INFO_BUFFER_SIZE;
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	GetUserNameW(infoBuf, &bufCharCount);
	string usrname = ConvTCHARtoSTR(infoBuf);
	return usrname;
}


int PutApkInRegistry()
{
	setlocale(LC_ALL, "ru");
	subcore_graphUnit_reg reporter;
	reporter.check_status_subcore_graphUnit_reg(true);
	printf("Введите название приложения: \n");
	string res;
	cin >> res;
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	wstring wide = converter.from_bytes(res);
	const wchar_t* result = wide.c_str();
	string username= GetUserNameQ();
	string path = "C:\\Users\\" + username + "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\" + res +".lnk";
	TCHAR exePath[1024];
	_tcscpy_s(exePath, CA2T(path.c_str()));

	HKEY hg;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hg) == ERROR_SUCCESS)
	{
		RegSetValueEx(hg, (LPCWSTR)result, NULL, REG_SZ, (BYTE*)exePath, sizeof(exePath));
		RegCloseKey(hg);
	}
	else
	RegCloseKey(hg);
	return true;
}

int main()
{
	int count;
	printf("Input member[1 - install/ 2 - Setup Menu]: ");
	cin >> count;
	while (true)
	{
		try
		{
			switch (count)
			{
			case 1:
				MainAutoinstall();
				break;
			case 2:
				PutApkInRegistry();
				break;
			}
		}
		catch (const std::exception&)
		{
			printf("Can't start the programm! \n");
		}
	}
}