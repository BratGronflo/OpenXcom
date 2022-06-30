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


int Server(int argc, char* argv[])
{
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
		listen(s, SOMAXCONN);
		
		//Wait for a connection
		sockaddr_in client;
		int clientsize = sizeof(client);
		SOCKET Client = accept(s, (SOCKADDR*)&hint, &sizeofaddr);
		char host[NI_MAXHOST];	  // Client's remote name
		char service[NI_MAXHOST]; // Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); // same as memset
		ZeroMemory(service, NI_MAXHOST);

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			std::cout << host << " connected on port " << service << std::endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			std::cout << host << " connected on port " <<
				ntohs(client.sin_port) << std::endl;
		}

		//TEST Feature LOOP: accept and echo message to client
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
				break;
			}

			// Echo message back to client
			send(s, buf, bytesReceived + 1, 0);
		}

		// Close listening socket
		closesocket(s);

		// Clean Winsock
		WSACleanup();
}

