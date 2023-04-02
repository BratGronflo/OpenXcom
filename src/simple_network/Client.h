#pragma once
#include "winsock2.h"
#include <vector>
#include <stdint.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

class FileClient{
private:
   WSADATA WsaData;
   SOCKET Socket;
   struct hostent* host;
   SOCKADDR_IN SockAddress;

   uint32_t recSizeInBytes;//total size of sent file in bytes
   std::vector<char> eVec;//will contain the file extension (a pdf file would mean this var holds ".pdf")
   uint32_t extensionLength;//will receive the length of the extension in characters

   std::string newFileName;//this will locally store whatever the user wants to name new file

public:
   FileClient();
   virtual ~FileClient();

   int initWinsock();
   int initSocket();

   void start(const std::string &filename);
   void close();

   uint32_t getSizeInBytes();
   std::vector<char> getExtension();

   void receiveData();

};
