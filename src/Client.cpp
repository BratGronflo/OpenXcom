#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 4096
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <winsock.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <vector>
#include <thread>
#include <string>
#pragma warning(disable : 4996)
#include "../src/Server.h"
#include "../src/Client.h"

using namespace OpenXcom;

int ServerClient::Client(int argc, char* argv[])
{
	void initiate();
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
	hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(30000);
	hint.sin_family = AF_INET;


	// Create socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
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
			return 7;
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
			return 3;
		}
		else
		{
			std::cerr << "Connection to server successfull!" << std::endl;
			_connectedToHost = true;
			return 10;
		}

	}
	
	char buf[4096];
	std::string str = ("HELLO!");
	const char* cstr = str.c_str();
	{

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
	//close down everything
	closesocket(s);
	WSACleanup();
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
