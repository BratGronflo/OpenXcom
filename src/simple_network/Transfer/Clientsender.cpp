#include <cstring>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <winsock2.h>
#pragma warning(disable : 4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define PORT 60000
#pragma comment(lib, "ws2_32.lib")
using namespace std;

struct fileMessageC
{
	char fileName[256];
	long int fileSize;
} fileMsg;
struct ArckMessageC
{
	char ok[10];
	unsigned long fileOffset;
} arkMsg;

int ClientSender()
{
	int sock_client;                           // Client socket
	struct sockaddr_in server_addr;            // server end address
	int addr_len = sizeof(struct sockaddr_in); // address length
	char msgbuffer[5000];                      // Receive message buffer
	struct hostent *hptr;
	char IP[50]; // IP address
	char hostname[256];
	/*establish connection*/
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Load Winsock.dll failed! \ N");
		return 1;
	}

	// *Create a socket * /
		if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "create sock error! The wrong number is " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}

	// *Get file name * /
		char path[200];
	getchar();
	cout << "Enter file path:" << endl;
	cin.getline(path, 200);
	char *filename = strrchr(path, '\\');
	if (filename)
	{
		filename++;
	}
	strcpy(fileMsg.fileName, filename);
	printf("file name is %s\n", filename);

	// *Open transfer file * /
		ifstream inFile(path, ios::in | ios::binary);
	if (!inFile.is_open())
	{
		cout << "Unable to open the file:" << path << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}

	// *Get file length * /
		inFile.seekg(0, ios::end);
	int size;
	size = inFile.tellg();

	// *Server address fill in * /
		memset(&server_addr, 0, addr_len); // clear the client address 0
	server_addr.sin_family = AF_INET;       // / Set the address family for IPv4
	server_addr.sin_port = htons(PORT);         // Set the port to port
	server_addr.sin_addr.S_un.S_addr = inet_addr(IP);

	// *Establish a connection with the server * /
		if (connect(sock_client, (struct sockaddr *)&server_addr, addr_len) != 0)
	{
		cout << "connect error! Wrong number is " << WSAGetLastError() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "The connection server is successful!" << endl;
	}

	// *Receive information and display * /
		int sizeR;
	if ((sizeR = recv(sock_client, msgbuffer, sizeof(msgbuffer), 0)) < 0)
	{
		cout << "receive message error! Wrong number is " << WSAGetLastError() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 1;
	}
	else if (sizeR == 0)
	{
		cout << "connect is closed" << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	else
		cout << "The message is :" << msgbuffer << endl;

	// *Send a file name and its length * /
		fileMsg.fileSize = htonl(size);
	int sizeS;
	if ((sizeS = send(sock_client, (char *)&fileMsg, sizeof(fileMsg), 0)) < 0)
		cout << "send message error! Wrong number is " << WSAGetLastError() << endl;
	else if (size == 0)
		cout << "the connection is closed" << endl;
	else
		cout << "message name and length successfully!" << endl;

	// *Receive the other party's OK information and file tail pointer * / if (recv(sock_client, (char *)&arkMsg, sizeof(arkMsg), 0) <= 0)
	{
		cout << "Receive OK failed \ n" << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	cout << "Receive OK success!" << endl;
	// *Mobile file reading position pointer * /
		int pos = ntohl(arkMsg.fileOffset);
	inFile.seekg(0, ios::beg);
	// *Send file content * /
		char fileBuffer[1000];
	if (strcmp(arkMsg.ok, "Allowed") == 0)
	{
		while (!inFile.eof())
		{
			int count;
			inFile.read(fileBuffer, sizeof(fileBuffer));
			count = inFile.gcount();
			send(sock_client, fileBuffer, count, 0);
			cout << "Send progress:" << inFile.tellg() << "\\" << size << endl;
		}
		cout << "file transfer finished" << endl;
		inFile.close();
	}
	else
	{
		cout << "The other party cannot receive documents" << endl;
	}
	/*Finish*/
	closesocket(sock_client);
	WSACleanup();
	return 0;
}
