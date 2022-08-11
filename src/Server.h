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
	ServerHost();
	void initiate_s();
	void hintstruct_s();
	void socketcreate();
	void binding_s();
	void waitforconnection();
	void acceptclient();
	void send_file();
	// is the Client  connected
	bool isClientConnected();
	// is game hosted
	bool isGameHosted();
};

}
