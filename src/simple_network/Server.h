#pragma once
#include "FileCopier.h"
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")

class FileServer{
private:
   WSADATA WsaData;
   SOCKET Socket;
   SOCKADDR_IN serverInfo;
public:
   FileServer();
  virtual ~FileServer();

   int initWinsock();
   int initSocket();

   void start(const std::string &filename);
   void close();

   void sendData(FileCopier& f);

};
