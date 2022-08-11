#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 4096
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <vector>
#include <thread>
#include <string>
#include <source_location>
#pragma warning(disable : 4996)
#include "../src/Server.h"
#include "../src/Client.h"

using namespace OpenXcom;

SOCKET serv;
SOCKADDR_IN hint_c;
bool _connectedToHost;

	void ServerClient::initiate_c()
	{
		// Initialize WinSock
		_connectedToHost = false;
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
			return;
		}
		else
		{
			std::cerr << "WSAStartup successfull" << std::endl;
		}
	}
	void ServerClient::hintstruct_c()
	{
		hint_c.sin_addr.s_addr = inet_addr("127.0.0.1");
		hint_c.sin_port = htons(30000);
		hint_c.sin_family = AF_INET;
	}
	void ServerClient::socketcreate_c()
	{
		SOCKET serv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (serv == INVALID_SOCKET)
		{
			std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
			WSACleanup();
			return;
		}
		else
		{
			std::cerr << "Socket Creation Successfull!" << std::endl;
		}
	}
	void ServerClient::binding_c()
	{
		bind(serv, (SOCKADDR*)&hint_c, sizeof(hint_c));
		if (serv == INVALID_SOCKET)
		{
			printf("bind failed");
			return;
		}
	}
	void ServerClient::connectiontoserv()
	{
		// Connect to server
		int Connection = connect(serv, (sockaddr*)&hint_c, sizeof(hint_c));
		if (Connection == SOCKET_ERROR)
		{
			std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
			closesocket(serv);
			WSACleanup();
			return;
		}
		else
		{
			std::cerr << "Connection to server successfull!" << std::endl;
			_connectedToHost = true;
		}

	}
	void ServerClient::recv_file()
{
	char file_size_str[16];
	char file_name[32];

	recv(serv, file_size_str, 16, 0);
	int file_size = std::atoi(file_size_str);
	char* bytes = new char[file_size];

	recv(serv, file_name, 32, 0);

	std::fstream file;
	file.open(file_name, std::ios_base::out | std::ios_base::binary);

	std::cout << "size: " << file_size << std::endl;
	std::cout << "name: " << file_size << std::endl;

	if (file.is_open())
	{
		recv(serv, bytes, file_size, 0);
		std::cout << "data: " << bytes << std::endl;

		file.write(bytes, file_size);
		std::cout << "ok save" << std::endl;
	}
	else
	{
		std::cout << "Error file open" << std::endl;
		delete[] bytes;
		file.close();
	}
}

	bool ServerClient::isConnectedToHost()
	{

		if (_connectedToHost == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
