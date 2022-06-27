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


int Client(int argc, char* argv[])
{

	WSADATA wsaData;

	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	char recvbuf[4096];
	char sendbuf[4096];
	int sendbuflen[DEFAULT_BUFLEN];
	int recvbuflen[DEFAULT_BUFLEN];

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(30000);
	addr.sin_family = AF_INET;
	SOCKET s = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) != 0); {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	return 0;
}
