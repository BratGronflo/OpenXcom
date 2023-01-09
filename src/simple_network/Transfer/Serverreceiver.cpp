#include<iostream>
#include<winsock2.h>
#include<cstring>
#include<direct.h>
#include<fstream>
#define PORT 60000 // Define port numbers
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

struct fileMessage
{
	char fileName[256];
	long int fileSize;
}fileMsg;
struct ArckMessage
{
	char ok[10];
	unsigned long fileOffset;
}arkMsg = { "Allowed", 0 };

int mainCatcher(int argc, char** argv)
{
	// * Define related variables * /
		SOCKET sock_server, sock_connect; // Define listening sockets and connect sockets
	struct sockaddr_in addr_server, addr_client; // Define server address and client address
	int size_addr = sizeof(sockaddr_in); // Define the address length
	char msg_buffer[256]; // Define buffers that receive information
	char msg[] = "Connection has established \ n"; // Define information sent to the client
	int size_data; // Define the length of the data sent or received
	// * Load Dynamic Link Library * /
		WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Load Winsock.dll failed!" << endl;
		return 1;
	}
	int sock_client;    // Client socket
	struct sockaddr_in server_addr;    // server end address
	int addr_len = sizeof(struct sockaddr_in);    // address length
	char msgbuffer[1000];        // Concking message buffer
	struct hostent* hptr;
	char* IP;// IP address
	char hostname[256];



	if (gethostname(hostname, sizeof(hostname)))
	{
		cout << "get hostname error!";
		WSACleanup();
		return 1;
	}
	if ((hptr = gethostbyname(hostname)) == NULL)
	{
		cout << "get id error!";
		WSACleanup();
		return 1;
	}
	IP = inet_ntoa(*(struct in_addr*)hptr->h_addr_list[0]);
	printf("Server IP:% S \ N", IP);

	// *** Create a listener cover *** /
	if ((sock_server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "Creating a socket failed! Error code:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	// *** Set the server address *** /
	memset(&addr_server, 0, size_addr);        // clear the server address 0
	addr_server.sin_family = AF_INET;       // Set the address family for IPv4
	addr_server.sin_port = htons(PORT);         // Set the port to port
	addr_server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  // Set any IP address allowed to use this unit
	// *** Listening socket binding server address *** /
	bind(sock_server, (SOCKADDR *)&addr_server, size_addr);
	if (sock_server == INVALID_SOCKET)
	{
		printf("bind failed");
		closesocket(sock_server);
		WSACleanup();
		return 1;
	}
	// *** Listening socket set to monitor status **** /
	if (listen(sock_server, SOMAXCONN) != 0)
	{
		cout << "Listen function call failed! Error code:" << WSAGetLastError() << endl;
		closesocket(sock_server);
		WSACleanup();
		return 1;
	}
	cout << "The server is listening ..." << endl;
	// *** Cycle service *** /

	while (true)
	{
		// *** Accept connection request *** /
		if ((sock_connect = accept(sock_server, (sockaddr*)&addr_client, &size_addr)) == INVALID_SOCKET)
		{
			// * cout << "accept function call failed! Error code: << Wsagetlasterror () << endl; * /
			continue;
		}
		cout << "Successfully accepts a connection request!" << endl;
		// *** Send information first *** /
		size_data = send(sock_connect, msg, sizeof(msg), 0);    // Send a message to the client MSG
		if (size_data == SOCKET_ERROR)
		{
			cout << "Send information failed! Error code:" << WSAGetLastError() << endl;
			closesocket(sock_connect);
			continue;
		}
		else if (size_data == 0)
		{
			cout << "The other party has closed the connection!" << endl;
			closesocket(sock_connect);
			continue;
		}
		else
			cout << "Connection feedback is successful!" << endl;

		// * Define file transfer variables * /
		long int filelen;
		char filename[500] = "D:\\test\\";
		char fileBuffer[1000];
		// * File Save Directory * /
		_mkdir(filename);
		// * Receive file name and length * /
		int f;
		if ((filelen = recv(sock_connect, (char*)&fileMsg, sizeof(fileMsg), 0)) <= 0)
		{
			cout << "Not received file name and length, error code:" << WSAGetLastError() << endl;
			closesocket(sock_connect);
			continue;
		}
		cout << "Received file name:" << fileMsg.fileName << ", File length" << fileMsg.fileSize << endl;
		filelen = ntohl(fileMsg.fileSize);
		strcat(filename, fileMsg.fileName);  // Splicing path

		// * Open file and position file write pointer * /
		ofstream outFile(filename, ios::app | ios::binary);
		if (!outFile.is_open())
		{
			cout << "Cannot open" << filename << endl;
			closesocket(sock_connect);
			continue;
		}
		// * File write pointer moves to the end of the file, get its value and send * /
		outFile.seekp(0, ios::end);
		arkMsg.fileOffset = ntohl(outFile.tellp());
		send(sock_connect, (char*)&arkMsg, sizeof(arkMsg), 0);

		// * Receive file data and write files * /
		int size = 0;
		do
		{
			size = recv(sock_connect, fileBuffer, sizeof(fileBuffer), 0);
			outFile.write(fileBuffer, size);
			filelen -= size;
			cout << "filelen is:" << filelen << endl;
		} while (size != 0 && filelen > 0);
		cout << "Transfer finished!\n";
		outFile.close();
		closesocket(sock_connect);
	}
	// *** End Procedure *** /
	closesocket(sock_server);       // Close the listening sleeve
	WSACleanup();       // Logout Dynamic Link Library
	return 0;
}
