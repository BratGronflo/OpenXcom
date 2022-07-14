#pragma once
#include "../src/Engine/Game.h"
#include "../src/Engine/State.h"


// Initialize the Server
namespace OpenXcom
{
	class ServerClient : public State
	{
	  private:
		bool _connectedToHost;

	  public:
		// Initialize the Client
		int Client(int argc, char *argv[]);
	};
 }
