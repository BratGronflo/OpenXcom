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

int ServerHost::Server(int argc, char* argv[])
{
	void initiate();
	{
		_connectionEstablished = false;
		_gameHosted = false;
		WSADATA wsaData;

		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{
			printf("WSAStartup failed: %d\n", iResult);
			return 1;
		}
		else
		{
			printf("WSAStartup successful");
			return 2;
		}
	}
		SOCKADDR_IN hint;
		int sizeofaddr = sizeof(hint);
		hint.sin_addr.s_addr = inet_addr("127.0.0.1");
		hint.sin_port = htons(30000);
		hint.sin_family = AF_INET;
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			printf("Socket creation failed");
			return 5;
		}
		else
		{
			printf("Socket creation successful");
			return 6;
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
	void waitforconnection();
	{
		// This socket is for listening
		listen(s, SOMAXCONN); //Wait for a connection
		if (listen(s, SOMAXCONN))
		{
			printf("listen started wait for client!");
			_gameHosted = true;
		}
	}
	SOCKET Client;
	void acceptclient();
	{

		sockaddr_in client;
		int clientsize = sizeof(client);
		Client = accept(s, (SOCKADDR*)&hint, &sizeofaddr);
		if (s == INVALID_SOCKET)
		{
			printf("failed to accept client!");
			return 8;
		}
		else
		{
			printf("Client connected!");
			return 9;
		}
	}
	Sleep(1500);

void TransferData(int argc, char* argv[]);
{
	//TEST Feature LOOP: accept and echo message to client, there will be feature like sending game Seed and other network actions.
		char buf[4096];
		std::string str = ("HELLO!");
		const char* cstr = str.c_str();
		while (true)
		{
			ZeroMemory(buf, 4096);

			//Wait for client to send data
			int bytesReceived = recv(s, buf, 4096, 0);
			if (bytesReceived == SOCKET_ERROR)
			{
				std::cerr << "Error in recv()" << std::endl;
				break;
			}
			if (bytesReceived == 0)
			{
				std::cout << "Client disconnected " << std::endl;
				_connectionEstablished = false;
				break;
			}

			// Echo message back to client
			send(s, buf, bytesReceived + 1, 0);
		}
}

// this also belongs to Server func //

		// Close listening socket
		closesocket(s);
		closesocket(Client);

		// Clean Winsock
		WSACleanup();
		return 0;
}
bool ServerHost::isClientConnected()
{

	if (_connectionEstablished == true)
	{
	return true;
	}
	else
	{
	return false;
	}
}
bool ServerHost::isGameHosted()
{
	if (_gameHosted == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
