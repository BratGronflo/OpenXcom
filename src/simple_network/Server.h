#pragma once
#include "FileCopier.h"
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")

class Server{
private:
   WSADATA WsaData;
   SOCKET Socket;
   SOCKADDR_IN serverInfo;
public:
   Server();
   virtual ~Server();

   int initWinsock();
   int initSocket();

   void start(const std::string &filename);
   void close();

   void sendData(FileCopier& f);

};
