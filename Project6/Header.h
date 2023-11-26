#pragma once
#include <iostream>
#include <windows.h>
//#include <winsock2.h>
//#include <WS2tcpip.h>
//#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>

//#pragma comment(lib, "Ws2_32.lib")

#include "Graph.h"

using namespace std;

class  CheckADB
{
private:
	char IP[20] = "127.0.0.1";
	int start = 58526, temp, err, nret;
	SOCKET sock;
	SOCKADDR_IN Info;
	LPWSADATA wsadata;
public:
	subcore_graphUnit_inst report;
	/*template<typename T> T from_strings(const std::string& str)
	{
		std::stringstream ss(str);
		T t;
		ss >> t;
		return t;
	}

	template<> std::string from_strings(const std::string& str)
	{
		return str;
	}*/

	bool ConnectToStandartIP()
	{
		try
		{
			system("adb connect 127.0.0.1:58526");
			return true;
		}
		catch (const std::exception&)
		{
			report.create_critical_neg_rep("No connection to the Android Debug Bridge server");
			return false;
		}
	}
	bool ConnectToCustomIP(string IPcustom)
	{
		try
		{
			string str = "adb connect " + IPcustom;
			char* URLs =  _strdup(str.c_str());
			system(URLs);
		}
		catch (const std::exception&)
		{
			report.create_critical_neg_rep("No connection to the Android Debug Bridge server");
			return false;
		}
	}
	bool checkADBinDir()
	{
		ifstream ADBopen("adb.exe");
		if (ADBopen.bad() != true)
		{
			report.create_pos_rep("Checking for adb.exe...successful");
			return true;
		}
			
		else
			return false;
	}
	bool checkADBserver()
	{
		/*char IP[20] = "127.0.0.1";
		int start = 58526, temp, err, nret;
		SOCKET sock;
		SOCKADDR_IN Info;
		WSADATA wsadata;
		err = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (err != 0)
		{
			report.create_neg_rep("Проблемы с винсокетом");
			cin.get();
			return false;
		}
		cin.ignore();

		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		Info.sin_family = AF_INET;
		Info.sin_port = htons(start);
		nret = connect(sock, NULL, NULL);
		if (nret != SOCKET_ERROR)
		{
			report.create_pos_rep("Сервер доступен...");
			closesocket(sock);
			return true;

		}
		else
		{
			report.create_neg_rep("Сервер недоступен");
			closesocket(sock);
			return false;

		}*/
		return true;
	}
};

class CheckApk
{
public:
	string lastStrings(ifstream& ADBopen)
	{
		string str;
		getline(ADBopen, str);
		return str;
	}
	bool checkInstallSuccess(string path)
	{
		ifstream ADBopen(path);
		if (ADBopen.bad() != true)
		{
			string str;
			getline(ADBopen, str);
			getline(ADBopen, str);
			if (str == "Success")
			{
				return true;
			}
		}

		return false;
	}
};

class InstallApk :  CheckADB, CheckApk
{
public:
	bool installapk(string path)
	{
		try
		{
			string srt = "adb install " + path + " >> installLog.txt";
			const char* URLs = _strdup(srt.c_str());
			system(URLs);
			if (checkInstallSuccess("installLog.txt") == true)
			{
				report.create_pos_rep("Install Success!");
				exit(EXIT_SUCCESS);
			}
			else
			{
				report.create_critical_neg_rep("Error install...");
				return false;
			}
			
		}
		catch (const std::exception&)
		{
			report.create_critical_neg_rep("Error, check log in installLog.txt");
			return false;
		}
	}
};

void autoStartUp()
{
	subcore_graphUnit_inst reporter;
	InstallApk aps;
	string apkpath;
	reporter.create_nos_rep("Please, input filepath[WITHOUT QUOTATION MARKS]:");
	cin >> apkpath;
	aps.installapk(apkpath);
}

void MainAutoinstall()
{
	setlocale(LC_ALL, "ru");
	subcore_graphUnit_inst reporter;
	reporter.check_status_subcore_graphUnit_inst(true);
	setlocale(LC_ALL, "ru");
	reporter.create_nos_rep("Use the default IP to connect to ADB?[127.0.0.1:58526] {Y/N}");
	string s;
	cin >> s;
	CheckADB app;
	CheckApk apk;

	if (app.checkADBinDir() == true)
	{
		if (app.checkADBserver() == true && s == "Y")
		{
			if (app.ConnectToStandartIP() == true)
			{
				reporter.create_pos_rep("All checks passed successfully!");
				autoStartUp();
			}
			
		}
		else if (app.checkADBserver() == true && s == "N")
		{
			string customIP;
			printf("Input device IP and port[EXAMPLE <127.0.0.1:77777>]: ");
			cin >> customIP;
			if (app.ConnectToCustomIP(customIP) == true)
			{
				reporter.create_pos_rep("All checks passed successfully!");
				autoStartUp();
			}
		}
		else
		{
			reporter.create_pos_rep("Unable to connect to WSA! Check if developer mode is active");
		}
	}
}