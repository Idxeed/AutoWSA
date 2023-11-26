#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>>
#include <windows.h>
#include <codecvt>
#include <tlhelp32.h>
#include <psapi.h>
#include <tchar.h>

using namespace std;



class Core_Graph abstract
{
public:
	
	
	virtual void create_pos_rep(string MSG) {};
	virtual void create_neg_rep(string MSG) {};
	virtual void create_nos_rep(string MSG) {};
	virtual void create_critical_neg_rep(string MSG) {};
	virtual void loadbar() {};
};

class subcore_graphUnit_reg : Core_Graph
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	COORD cmdSize = { lpConsoleScreenBufferInfo.dwSize.X * lpConsoleScreenBufferInfo.dwSize.Y };
	COORD cursorPosition = { lpConsoleScreenBufferInfo.dwCursorPosition.X * lpConsoleScreenBufferInfo.dwCursorPosition.Y };
	SMALL_RECT cmdRegion = { lpConsoleScreenBufferInfo.srWindow.Left, lpConsoleScreenBufferInfo.srWindow.Top, lpConsoleScreenBufferInfo.srWindow.Right, lpConsoleScreenBufferInfo.srWindow.Bottom };
	void getDataConsoleWE(HANDLE& hConsol, CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInf)
	{
		if (!GetConsoleScreenBufferInfo(hConsol, &lpConsoleScreenBufferInf))
		{
			exit(EXIT_FAILURE);
		}
	}

	HANDLE hNewScreenBuffer1 = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared
		NULL,                    // default security attributes
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
		NULL);
	HANDLE hNewScreenBuffer2 = CreateConsoleScreenBuffer(
		GENERIC_READ |
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	

	int SetActiveBuffer()
	{
		if (SetConsoleActiveScreenBuffer(hNewScreenBuffer1) == NULL)
		{
			SetConsoleActiveScreenBuffer(hNewScreenBuffer2);
			return 2;
		}
		else
		{
			SetConsoleActiveScreenBuffer(hNewScreenBuffer1);
			return 1;
		}
	}
	bool stat;
public:
	subcore_graphUnit_reg()
	{
		setlocale(LC_ALL, "ru");
		getDataConsoleWE(hConsole, lpConsoleScreenBufferInfo);
	}
	void check_status_subcore_graphUnit_reg(bool status = false)
	{
		try
		{
			if (status == false)
			{
				printf("[-] Status subcore_graphUnit_reg: false. Can't active.. \n");
				stat = status;
			}
			else
			{
				printf("[+] Status subcore_graphUnit_reg...OK;");
				stat = status;
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void create_pos_rep(string MSG) override
	{
		try
		{
			if (stat == true)
			{
				printf("[+] %s", MSG);
			}
			else
			{
				printf("[-] Check status subcore_graphUnit_reg..");
				check_status_subcore_graphUnit_reg();
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
			check_status_subcore_graphUnit_reg();
		}
	}
	virtual void create_neg_rep(string MSG) override
	{
		try
		{
			if (stat = true)
				printf("[-] %s", MSG);
			else
			{
				printf("[-] Check status subcore_graphUnit_reg..");
				check_status_subcore_graphUnit_reg();
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void create_nos_rep(string MSG) override
	{
		try
		{
			if (stat = true)
				printf("[*] %s", MSG);
			else
			{
				printf("[-] Check status subcore_graphUnit_reg..");
				check_status_subcore_graphUnit_reg();
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void create_critical_neg_rep(string MSG) override
	{
		try
		{
			if (stat = true)
			{
				printf("[!] %s", MSG);
				exit(EXIT_FAILURE);
			}	
			else
			{
				printf("[-] Check status subcore_graphUnit_reg..");
				check_status_subcore_graphUnit_reg();
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void loadbar() override
	{
		SMALL_RECT srctScrollRect, srctClipRect;
		COORD CoordDis;
		CHAR_INFO chiFill;

		if (lpConsoleScreenBufferInfo.dwSize.Y == 30 && lpConsoleScreenBufferInfo.dwSize.X == 120)
		{
			srctScrollRect.Top = lpConsoleScreenBufferInfo.dwSize.Y - 1;//use (Y-(int) numb)) to change the line
			srctScrollRect.Bottom = lpConsoleScreenBufferInfo.dwSize.Y - 1;// use (Y-(int) numb)) to change the line
			srctScrollRect.Left = lpConsoleScreenBufferInfo.dwSize.X; // don't touch them
			srctScrollRect.Right = lpConsoleScreenBufferInfo.dwSize.X - 1; // Line Occupancy (X-(int) numb)) 

			srctClipRect = srctScrollRect;

			CoordDis.X = 0;
			CoordDis.Y = 0 - 17;

			chiFill.Attributes = BACKGROUND_GREEN;
			chiFill.Char.AsciiChar = (char)'#';

			if (!ScrollConsoleScreenBuffer(
				hConsole,         // screen buffer handle
				&srctScrollRect, // scrolling rectangle
				&srctClipRect,   // clipping rectangle
				CoordDis,       // top left destination cell
				&chiFill));    // fill character and color
			{
				printf("ScrollConsoleScreenBuffer failed %d\n", GetLastError());
			}
		}	//дописать сюда версию под любой размер консоли 

	}
};

class subcore_graphUnit_inst : Core_Graph
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	COORD cmdSize = { lpConsoleScreenBufferInfo.dwSize.X * lpConsoleScreenBufferInfo.dwSize.Y };
	COORD cursorPosition = { lpConsoleScreenBufferInfo.dwCursorPosition.X * lpConsoleScreenBufferInfo.dwCursorPosition.Y };
	SMALL_RECT cmdRegion = { lpConsoleScreenBufferInfo.srWindow.Left, lpConsoleScreenBufferInfo.srWindow.Top, lpConsoleScreenBufferInfo.srWindow.Right, lpConsoleScreenBufferInfo.srWindow.Bottom };
	void getDataConsoleWE(HANDLE& hConsol, CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInf)
	{
		if (!GetConsoleScreenBufferInfo(hConsol, &lpConsoleScreenBufferInf))
		{
			exit(EXIT_FAILURE);
		}
	}
	
	HANDLE hNewScreenBuffer1 = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared
		NULL,                    // default security attributes
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
		NULL);
	HANDLE hNewScreenBuffer2 = CreateConsoleScreenBuffer(
		GENERIC_READ |
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

	int SetActiveBuffer()
	{
		if (SetConsoleActiveScreenBuffer(hNewScreenBuffer1) == NULL)
		{
			SetConsoleActiveScreenBuffer(hNewScreenBuffer2);
			return 2;
		}
		else
		{
			SetConsoleActiveScreenBuffer(hNewScreenBuffer1);
			return 1;
		}
	}
	bool stat=true;
public:

	subcore_graphUnit_inst()
	{
		getDataConsoleWE(hConsole, lpConsoleScreenBufferInfo);
		
	}

	void check_status_subcore_graphUnit_inst(bool status)
	{

		try
		{
			if (status == false)
			{
				printf("[-] Status subcore_graphUnit_inst: false. Can't active.. \n");
				stat = status;
			}
			else
			{
				printf("[+] Status subcore_graphUnit_inst...OK \n");
				stat = status;
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void create_pos_rep(string MSG) override
	{
		try
		{
			if (stat == true)
			{
				printf("[+] %s \n", MSG.c_str());
			}
			else
			{
				printf("[*] Check status subcore_graphUnit_inst..\n");
				
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		
		}
	}
	virtual void create_neg_rep( string MSG) override
	{
		try
		{
			if (stat = true)
			{
				printf("[-] %s", MSG.c_str());
			}
			else
			{
				printf("[*] Check status subcore_graphUnit_reg..\n");
				
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void create_nos_rep(string MSG) override
	{
		try
		{
			if (stat = true)
				printf("[*] %s", MSG.c_str());
			else
			{
				printf("[*] Check status subcore_graphUnit_reg..\n");
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void create_critical_neg_rep(string MSG) override
	{
		try
		{
			if (stat = true)
			{
				printf("[!] %s", MSG.c_str());
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("[-] Check status subcore_graphUnit_reg..\n");
			}
		}
		catch (const std::exception&)
		{
			printf("%d\n", GetLastError());
		}
	}
	virtual void loadbar() override
	{
		SMALL_RECT srctScrollRect, srctClipRect;
		COORD CoordDis;
		CHAR_INFO chiFill;

		if (lpConsoleScreenBufferInfo.dwSize.Y == 30 && lpConsoleScreenBufferInfo.dwSize.X == 120)
		{
			srctScrollRect.Top = lpConsoleScreenBufferInfo.dwSize.Y - 1;//use (Y-(int) numb)) to change the line
			srctScrollRect.Bottom = lpConsoleScreenBufferInfo.dwSize.Y - 1;// use (Y-(int) numb)) to change the line
			srctScrollRect.Left = lpConsoleScreenBufferInfo.dwSize.X; // don't touch them
			srctScrollRect.Right = lpConsoleScreenBufferInfo.dwSize.X - 1; // Line Occupancy (X-(int) numb)) 

			srctClipRect = srctScrollRect;

			CoordDis.X = 0;
			CoordDis.Y = 0 - 17;

			chiFill.Attributes = BACKGROUND_GREEN;
			chiFill.Char.AsciiChar = (char)'#';

			if (!ScrollConsoleScreenBuffer(
				hConsole,         // screen buffer handle
				&srctScrollRect, // scrolling rectangle
				&srctClipRect,   // clipping rectangle
				CoordDis,       // top left destination cell
				&chiFill));    // fill character and color
			{
				printf("ScrollConsoleScreenBuffer failed %d\n", GetLastError());
			}
		}	//дописать сюда версию под любой размер консоли 
	}
};

//int GDICreateBanner()
//{
//	::_setmode(::_fileno(stdout), _O_U16TEXT);
//	auto const& sz_message
//	{
//		L" █████╗ ██╗   ██╗████████╗ ██████╗ ██╗    ██╗███████╗ █████╗ " L"\n"
//		L"██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗██║    ██║██╔════╝██╔══██╗" L"\n"
//		L"███████║██║   ██║   ██║   ██║   ██║██║ █╗ ██║███████╗███████║" L"\n"
//		L"██╔══██║██║   ██║   ██║   ██║   ██║██║███╗██║╚════██║██╔══██║" L"\n"
//		L"██║  ██║╚██████╔╝   ██║   ╚██████╔╝╚███╔███╔╝███████║██║  ██║" L"\n"
//		L"╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝  ╚══╝╚══╝ ╚══════╝╚═╝  ╚═╝" L"\n"
//	};
//	::std::wcout << sz_message << ::std::flush;
//	::_wsystem(L"pause");
//	return true;
//}