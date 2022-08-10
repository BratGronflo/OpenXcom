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


int ServerClient::Client(int argc, char* argv[])
{
	void initiate_c();
	{
		// Initialize WinSock
		_connectedToHost = false;
		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
			return 1;
		}
		else
		{
			std::cerr << "WSAStartup successfull" << std::endl;
		}
	}
	

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_addr.s_addr = inet_addr("127.0.0.1");
	hint.sin_port = htons(30000);
	hint.sin_family = AF_INET;


	// Create socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return 2;
	}
	else
	{
		std::cerr << "Socket Creation Successfull!" << std::endl;
	}
	void binding();
	{
		bind(s, (SOCKADDR*)&hint, sizeof(hint));
		if (s == INVALID_SOCKET)
		{
			printf("bind failed");
			return 3;
		}
	}
	void connectiontoserv();
	{
		// Connect to server
		int Connection = connect(s, (sockaddr*)&hint, sizeof(hint));
		if (Connection == SOCKET_ERROR)
		{
			std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
			closesocket(s);
			WSACleanup();
			return 4;
		}
		else
		{
			std::cerr << "Connection to server successfull!" << std::endl;
			_connectedToHost = true;
		}

	}
	void TransferData_c(int argc, char* argv[]);
	{
		char buf[4096];
		std::string str = ("HELLO!");
		const char* cstr = str.c_str();

		// Send the text
		int sendResult = send(s, cstr, DEFAULT_BUFLEN, NULL);
		if (sendResult != SOCKET_ERROR)
		{
			// Wait for response
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(s, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				// Echo response to console
				std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
			}
		}
	}
	
}
void recv_file(SOCKET s)
{
	char file_size_str[16];
	char file_name[32];

	recv(s, file_size_str, 16, 0);
	int file_size = std::atoi(file_size_str);
	char* bytes = new char[file_size];

	recv(s, file_name, 32, 0);

	std::fstream file;
	file.open(file_name, std::ios_base::out | std::ios_base::binary);

	std::cout << "size: " << file_size << std::endl;
	std::cout << "name: " << file_size << std::endl;

	if (file.is_open())
	{
		recv(s, bytes, file_size, 0);
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
