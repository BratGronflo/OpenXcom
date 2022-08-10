#pragma once
#include "../src/Engine/Game.h"
#include "../src/Engine/State.h"
#include "../src/Server.h"

// Initialize the Server
namespace OpenXcom
{
	class ServerClient : public State
	{
	  private:
		bool _connectedToHost; //placeholder

	  public:
		// Initialize the Client
		  void initiate_c();
		  void hintstruct();
		  void binding_c();
		  void connectiontoserv();
		  void TransferData_c(int argc, char* argv[]);
		  void recv_file();
		int Client(int argc, char *argv[]);
		bool isConnectedToHost();
	};
 }
