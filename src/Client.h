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
		  void hintstruct_c();
		  void binding_c();
		  void socketcreate_c();
		  void connectiontoserv();
		  void recv_file();
		bool isConnectedToHost();
	};
 }
