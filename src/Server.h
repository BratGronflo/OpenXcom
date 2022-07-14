#pragma once
#include "../src/Engine/Game.h"
#include "../src/Engine/State.h"

namespace OpenXcom
// Initialize the Server
{


class ServerHost : public State
{
  private:
	bool _connectionEstablished; //placeholder

  public:
	// Initialize the Server
	int Server(int argc, char* argv[]);
	// is the Client  connected
	bool isClientConnected();

};

}
