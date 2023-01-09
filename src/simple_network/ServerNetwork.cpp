#include "StdAfx.h"
#include "ServerNetwork.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <SHLOBJ.H>
#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <vector>
#include <thread>
#include <string>
#include <source_location>

ServerNetwork::ServerNetwork(void)
{
	// create WSADATA object
    WSADATA wsaData;

    // our sockets for the server
    ListenSocket = INVALID_SOCKET;
    ClientSocket = INVALID_SOCKET;



    // address info for the server to listen to
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }

    // set address information
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;    // TCP connection!!!
    hints.ai_flags = AI_PASSIVE;

	    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(1);
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    // Set the mode of the socket to be nonblocking
    u_long iMode = 1;
    iResult = ioctlsocket(ListenSocket, FIONBIO, &iMode);

    if (iResult == SOCKET_ERROR) {
        printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }

    // no longer need address information
    freeaddrinfo(result);

    // start listening for new clients attempting to connect
    iResult = listen(ListenSocket, SOMAXCONN);

    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        exit(1);
    }
}


ServerNetwork::~ServerNetwork(void)
{
}

// accept new connections
bool ServerNetwork::acceptNewClient(unsigned int & id)
{
    // if client waiting, accept the connection and save the socket
    ClientSocket = accept(ListenSocket,NULL,NULL);

    if (ClientSocket != INVALID_SOCKET) 
    {
        //disable nagle on the client's socket
        char value = 1;
        setsockopt( ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );

        // insert new client into session id table
        sessions.insert( pair<unsigned int, SOCKET>(id, ClientSocket) );

        return true;
    }

    return false;
}

// receive incoming data
int ServerNetwork::receiveData(unsigned int client_id, char * recvbuf)
{
    if( sessions.find(client_id) != sessions.end() )
    {
        SOCKET currentSocket = sessions[client_id];
        iResult = NetworkServices::receiveMessage(currentSocket, recvbuf, MAX_PACKET_SIZE);

        if (iResult == 0)
        {
            printf("Connection closed\n");
            closesocket(currentSocket);
        }

        return iResult;
    }

    return 0;
}
void ServerNetwork::send_file(const std::string &filename)
{

	//= Options::getUserFolder()
	//= Options::getMasterUserFolder()
	// fullpathtest = "F:/My Documents/Documents/OpenXcom/xcom1/_autobattle_.asav";
	std::fstream file;
	// std::stringfilepathfinaltest = Options::getMasterUserFolder() + "_autobattle_.asav";
	//std::string filepath = Options::getMasterUserFolder() + filename;
	// std::vector<YAML::Node> filewhat = YAML::LoadAll(*CrossPlatform::readFile(filepath));
	file.open(filename, std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		int file_size = std::filesystem::file_size(filename) + 1;

		char *bytes = new char[file_size];

		file.read(bytes, file_size);

		std::cout << "size: " << file_size << std::endl;
		std::cout << "name: " << filename << std::endl;
		std::cout << "data: " << bytes << std::endl;

		send(ClientSocket, std::to_string(file_size).c_str(), 16, 0);
		send(ClientSocket, filename.c_str(), 32, 0);
		send(ClientSocket, bytes, file_size, 0);
		delete[] bytes;
	}
	else
		std::cout << "Error file open" + filename << std::endl;
	file.close();
}

// send data to all clients
void ServerNetwork::sendToAll(char * packets, int totalSize)
{
    SOCKET currentSocket;
    std::map<unsigned int, SOCKET>::iterator iter;
    int iSendResult;

    for (iter = sessions.begin(); iter != sessions.end(); iter++)
    {
        currentSocket = iter->second;
        iSendResult = NetworkServices::sendMessage(currentSocket, packets, totalSize);

        if (iSendResult == SOCKET_ERROR) 
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(currentSocket);
        }
    }
}
