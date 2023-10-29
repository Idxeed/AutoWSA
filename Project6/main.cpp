#include <iostream>
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <codecvt>

#include "GDIwsa.h"

#define ENV_VAR_STRING_COUNT  (sizeof(envVarStrings)/sizeof(TCHAR*))
#define INFO_BUFFER_SIZE 32767
#define _NO_CRT_STDIO_INLINE

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

	printf("[*] ������� �������� ����������: \n");
	string res;
	cin >> res;
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	wstring wide = converter.from_bytes(res);
	const wchar_t* result = wide.c_str();
	if (result != NULL)
		printf(" Convert string -> const wchar_t.. \n");
	else
		printf("Convert string -> const wchar_t.. \n");
	string username = GetUserNameQ();
	if (username != " ") 
		printf("Get username... \n");
	else 
		printf("Get username \n");
		
	string path = "C:\\Users\\" + username + "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\" + res + ".lnk";
	TCHAR exePath[1024];
	_tcscpy_s(exePath, CA2T(path.c_str()));
	HKEY hg;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hg) == ERROR_SUCCESS)
	{
		RegSetValueEx(hg, (LPCWSTR)result, NULL, REG_SZ, (BYTE*)exePath, sizeof(exePath));
		RegCloseKey(hg);

		printf("Create file in Registry! \n");
	}
	else
	{
		RegCloseKey(hg);
		printf("Create file in Registry! \n");
	}
	return true;
}

int main()
{
	int count;
	/*GDICreateBanner();*/
	printf("[~] Input member[1 - install/ 2 - Setup Menu]: ");
	cin >> count;
	while (true)
	{
		try
		{
			switch (count)
			{
			case 1:
				/*MainAutoinstall();*/
				printf("[*] Coming soon... \n");
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