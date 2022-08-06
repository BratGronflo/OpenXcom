#pragma once
#include "../src/Engine/Game.h"
#include "../src/Engine/State.h"
#include "../src/Client.h"

namespace OpenXcom
// Initialize the Server
{


class ServerHost : public State
{
  private:
	bool _connectionEstablished; //placeholder
	bool _gameHosted;			 //placeholder

  public:
	  int iResult;
	  char buf[];

	// Initialize the Server
	int Server(int argc, char* argv[]);
	void TransferData(int argc, char* argv[]);
	void initiate();
	void binding();
	void waitforconnection();
	void acceptclient();
	// is the Client  connected
	bool isClientConnected();
	// is game hosted
	bool isGameHosted();
};

}
