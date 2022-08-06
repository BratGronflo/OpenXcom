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
		  void initiate();
		  void binding();
		  void connectiontoserv();
		  void TransferData(int argc, char* argv[]);
		int Client(int argc, char *argv[]);
		bool isConnectedToHost();
	};
 }
