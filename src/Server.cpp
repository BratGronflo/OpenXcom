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
#include "../src/Engine/Options.h"

using namespace OpenXcom;

void send_file(SOCKET Client, const std::string& file_name)
{
	std::string fullpath;
	fullpath = Options::getMasterUserFolder();
	std::fstream file;
	file.open(file_name, std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		int file_size = std::experimental::filesystem::file_size(file_name) + 1;

		char* bytes = new char[file_size];

		file.read(bytes, file_size);

		std::cout << "size: " << file_size << std::endl;
		std::cout << "name: " << file_name << std::endl;
		std::cout << "data: " << bytes << std::endl;

		send(Client, std::to_string(file_size).c_str(), 16, 0);
		send(Client, file_name.c_str(), 32, 0);
		send(Client, bytes, file_size, 0);
		delete[] bytes;
	}
	else
		std::cout << "Error file open" << std::endl;
	file.close();
}
void ServerHost::initiate_s()
{
	_connectionEstablished = false;
	_gameHosted = false;
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}
	else
	{
		printf("WSAStartup successful");
	}
}
		void ServerHost::hintstruct()
		{
			SOCKADDR_IN hint;
			int sizeofaddr = sizeof(hint);
			hint.sin_addr.s_addr = inet_addr("127.0.0.1");
			hint.sin_port = htons(30000);
			hint.sin_family = AF_INET;
		}
		void ServerHost::socketcreate()
		{
			SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (s == INVALID_SOCKET)
			{
				printf("Socket creation failed");
				return;
			}
			else
			{
				printf("Socket creation successful");
			}
		}

	void ServerHost::binding_s()
	{
		bind(s, (SOCKADDR*)&hint, sizeof(hint));
		if (s == INVALID_SOCKET)
		{
			printf("bind failed");
			return;
		}
	}
	void ServerHost::waitforconnection()
	{
		// This socket is for listening
		listen(s, 1); //Wait for a connection
		if (listen(s, 1))
		{
			printf("listen started wait for client!");
			_gameHosted = true;
		}
	}
	void ServerHost::acceptclient()
	{
		SOCKET Client;
		sockaddr_in client;
		int clientsize = sizeof(client);
		Client = accept(s, (SOCKADDR*)&hint, &sizeofaddr);
		if (s == INVALID_SOCKET)
		{
			printf("failed to accept client!");
			return;
		}
		else
		{
			printf("Client connected!");
			std::thread Client_c;
		}
	}
	void ServerHost::TransferData_s()
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
			send(Client, buf, bytesReceived + 1, 0);
		}
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
