#pragma once
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



#ifdef UNICODE 
typedef LPCWSTR LPCTSTR;
#endif;

#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif

#define _NO_CRT_STDIO_INLINE

using namespace std;


class Programm
{
private:
	int n;
public:
	const wchar_t* ConvSTRtoWCHAR(string str)
	{

		wstring_convert <codecvt_utf8_utf16<wchar_t >> converter;
		wstring processname = converter.from_bytes(str);
		const wchar_t* newSTR = processname.c_str();
		return newSTR;
	}
	DWORD GetProcessPID(string processName)
	{

		//тут храним информацию о процессе
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		//делаем снапшот процессов 
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		const wchar_t* ProcessName = ConvSTRtoWCHAR(processName);
		//получаем 
		while (Process32First(snapshot, &entry) == true)
		{
			if (_wcsicmp(entry.szExeFile, ProcessName) == 0)
			{
				return entry.th32ProcessID;
			}
		}
	}
	bool IsProcessRun(std::string processName)
	{

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		PROCESSENTRY32 pe{};
		pe.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnapshot, &pe);
		const wchar_t* ProcessName = ConvSTRtoWCHAR(processName);

		while (1) {
			if (_wcsicmp(pe.szExeFile, ProcessName) == 0) return true;
			if (!Process32Next(hSnapshot, &pe)) return false;
		}
	}
	int GetInfoMemoryProc()
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 pc32 = { sizeof(pc32) };
		if (Process32First(snapshot, &pc32) == true)
			while (Process32First(snapshot, &pc32) == true)
			{
				HANDLE curHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pc32.th32ProcessID);
				PROCESS_MEMORY_COUNTERS_EX pmc;
				GetProcessMemoryInfo(curHandle, reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
				return pmc.PagefileUsage;
				break;

			}

	}
};

//class WinWindow
//{
//private:
//	int a;
//public:
//	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//	{
//		PAINTSTRUCT ps;
//		HDC hdc;
//		TCHAR mess[] = _T("Hello world!");
//
//		switch (uMsg)
//		{
//		case WM_PAINT:
//			hdc = BeginPaint(hwnd, &ps);
//			TextOut(hdc, 5, 5, mess, _tcsclen(mess));
//			EndPaint(hwnd, &ps);
//			break;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			break;
//		default:
//			break;
//		}
//
//	}
//	int WINAPI WinWindowQ(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//		PSTR lpCmdLine, int nCmdShow)
//	{
//
//		static TCHAR szWindowClass[] = _T("AutoWSA");
//		static TCHAR szTitle[] = _T("Windows Subsystenm for Android Installer");
//
//		WNDCLASSEX wcex;
//
//		wcex.cbSize = sizeof(WNDCLASSEX);
//		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS;
//		wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
//		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//		wcex.lpszClassName = szWindowClass;
//		wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
//
//		if (!RegisterClassEx(&wcex))
//		{
//			MessageBox(NULL,
//				_T("Call to RegisterClassEx failed!"),
//				_T("Windows Desktop Guided Tour"),
//				NULL);
//			return 1;
//		}
//
//		HWND hWnd = CreateWindowExA(
//			WS_EX_OVERLAPPEDWINDOW,
//			szWindowClass,
//			szTitle,
//			WS_OVERLAPPEDWINDOW,
//			CW_USEDEFAULT, CW_USEDEFAULT,
//			500, 100,
//			NULL,
//			NULL,
//			hInstance,
//			NULL
//		);
//		if (!hWnd)
//		{
//			MessageBox(NULL,
//				_T("Call to CreateWindowEx failed!"),
//				_T("Windows Desktop Guided Tour"),
//				NULL);
//
//			return 1;
//		}
//		ShowWindow(hWnd, nCmdShow);
//		UpdateWindow(hWnd);
//
//		MSG msg;
//		while (GetMessageA(&msg, NULL, 0, 0))
//		{
//			TranslateMessage(&msg);
//			DispatchMessageA(&msg);
//		}
//		return (int)msg.wParam;
//	}
//
//	int WINAPI CreateBottomWindow(HWND& parent_hwnd, LPCTSTR Text, int x, int y, int nWindth, int nHeight)
//	{
//		HWND hwndBottonWindow = CreateWindowW(
//			"Bottom",
//			Text,
//			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//			x,
//			y,
//			nWindth,
//			nHeight,
//			parent_hwnd,
//			NULL,
//			(HINSTANCE)GetWindowLongPtr(parent_hwnd, GWLP_HINSTANCE),
//			NULL
//		);
//	}
//};

class RenderCovn : public Programm
{
private:
	PCONSOLE_SCREEN_BUFFER_INFO getDataConsole(HANDLE& hConsole)
	{
		PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
		GetConsoleScreenBufferInfo(hConsole, lpConsoleScreenBufferInfo);
		return lpConsoleScreenBufferInfo;
	}


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo = getDataConsole(hConsole);
	COORD cmdSize = { lpConsoleScreenBufferInfo->dwSize.X * lpConsoleScreenBufferInfo->dwSize.Y };
	COORD cursorPosition = { lpConsoleScreenBufferInfo->dwCursorPosition.X * lpConsoleScreenBufferInfo->dwCursorPosition.Y };
	SMALL_RECT cmdRegion = { lpConsoleScreenBufferInfo->srWindow.Left, lpConsoleScreenBufferInfo->srWindow.Top, lpConsoleScreenBufferInfo->srWindow.Right, lpConsoleScreenBufferInfo->srWindow.Bottom };


	//for bar
	PCHAR_INFO buffer;
	SMALL_RECT lpClipRegion;

	//for write new str in screenbuffer
	LPCTSTR lpCharacter;
	DWORD len = 3;
	COORD dwWriteCoord;
	LPDWORD lpNumberOfCharWritten;


	//to write new text
	/*PCHAR_INFO newBuffer;
	COORD newBufferCoord{ lpConsoleScreenBufferInfo->dwSize.X * lpConsoleScreenBufferInfo->dwSize.Y };
	COORD newbufferCoordToWriteRead{ lpConsoleScreenBufferInfo->dwCursorPosition.X * lpConsoleScreenBufferInfo->dwCursorPosition.Y };
	SMALL_RECT newReadWriteRegion{ lpConsoleScreenBufferInfo->srWindow.Left, lpConsoleScreenBufferInfo->srWindow.Top, lpConsoleScreenBufferInfo->srWindow.Right, lpConsoleScreenBufferInfo->srWindow.Bottom };*/

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

	

public:
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
	void CreateWSAactiveTaskBar()
	{
		SMALL_RECT srctScrollRect, srctClipRect;
		COORD CoordDis;
		CHAR_INFO chiFill;

		if (lpConsoleScreenBufferInfo->dwSize.Y == 30 && lpConsoleScreenBufferInfo->dwSize.X == 120)
		{
			srctScrollRect.Top = lpConsoleScreenBufferInfo->dwSize.Y - 1;//use (Y-(int) numb)) to change the line
			srctScrollRect.Bottom = lpConsoleScreenBufferInfo->dwSize.Y - 1;// use (Y-(int) numb)) to change the line
			srctScrollRect.Left = lpConsoleScreenBufferInfo->dwSize.X; // don't touch them
			srctScrollRect.Right = lpConsoleScreenBufferInfo->dwSize.X - 1; // Line Occupancy (X-(int) numb)) 

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
				&chiFill))       // fill character and color
			{
				printf("ScrollConsoleScreenBuffer failed %d\n", GetLastError());

			}
		}
		//дописать сюда версию под любой размер консоли 

	}
	void WriteConsoleOutputAS()
	{
		if (SetActiveBuffer() == 1)
		{
			lpCharacter = (LPCTSTR)GetInfoMemoryProc();
			WriteConsoleOutputCharacter(
				hNewScreenBuffer1,
				lpCharacter,
				len,
				dwWriteCoord,
				lpNumberOfCharWritten
			);
		}
	}
};

void CreateRenderConv()
{

}




void GDICreateBanner()
{
	::_setmode(::_fileno(stdout), _O_U16TEXT);
	auto const& sz_message
	{
		L" █████╗ ██╗   ██╗████████╗ ██████╗ ██╗    ██╗███████╗ █████╗ " L"\n"
		L"██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗██║    ██║██╔════╝██╔══██╗" L"\n"
		L"███████║██║   ██║   ██║   ██║   ██║██║ █╗ ██║███████╗███████║" L"\n"
		L"██╔══██║██║   ██║   ██║   ██║   ██║██║███╗██║╚════██║██╔══██║" L"\n"
		L"██║  ██║╚██████╔╝   ██║   ╚██████╔╝╚███╔███╔╝███████║██║  ██║" L"\n"
		L"╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝  ╚══╝╚══╝ ╚══════╝╚═╝  ╚═╝" L"\n"
	};
	::std::wcout << sz_message << ::std::flush;
	//::_wsystem(L"pause");

}



void ActiveRender()
{

}
