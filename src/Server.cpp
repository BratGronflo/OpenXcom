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
	_connectionEstablished = false;
	_gameHosted = false;
	WSADATA wsaData;

	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, NULL);
	

		SOCKADDR_IN hint;
		int sizeofaddr = sizeof(hint);
		hint.sin_addr.s_addr = INADDR_ANY;
		hint.sin_port = htons(30000);
		hint.sin_family = AF_INET;

		bind(s, (SOCKADDR*)&hint, sizeof(hint));
		// This socket is for listening
		listen(s, SOMAXCONN); //Wait for a connection
		if (listen(s, SOMAXCONN))
		{
			_gameHosted = true;
		}
		sockaddr_in client;
		int clientsize = sizeof(client);
		SOCKET Client = accept(s, (SOCKADDR*)&hint, &sizeofaddr);
		char host[NI_MAXHOST];	  // Client's remote name
		char service[NI_MAXHOST]; // Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); // same as memset
		ZeroMemory(service, NI_MAXHOST);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			std::cout << host << " connected on port " << service << ntohs(client.sin_port) << std::endl;;
			_connectionEstablished = true; // jopper
		}

int TransferData(int argc, char* argv[]);
{
	//TEST Feature LOOP: accept and echo message to client, there will be feature like sending game Seed and other network actions.
		char buf[4096];

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

		// Clean Winsock
		WSACleanup();
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
