#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 4096
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <winsock.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <vector>
#pragma warning(disable : 4996)
#include <thread>
#include <string>

using namespace std;

int Client(int argc, char* argv[])
{
	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return 1;
	}

	// Create socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return 2;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(30000);
	hint.sin_family = AF_INET;

	// Connect to server
	int Connection = connect(s, (sockaddr*)&hint, sizeof(hint));
	if (Connection == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(s);
		WSACleanup();
		return 3;
	}

	// Do-while loop to send and receive data
	char buf[4096];
	std::string userInput;

	do
	{
		// Prompt the user for some text
		std::cout << "> ";
		getline (std::cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			int sendResult = send(s, userInput.c_str(), userInput.size() + 1, 0);
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

	} while (userInput.size() > 0);

	//close down everything
	closesocket(s);
	WSACleanup();
}
