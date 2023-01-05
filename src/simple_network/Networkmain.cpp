// main.cpp : Defines the entry point for the console application.
//

// may need #include "stdafx.h" in visual studio
#include "stdafx.h"
#include "ServerGame.h"
// used for multi-threading
#include <process.h>

void serverLoop(void *);

ServerGame * server;

<<<<<<< Updated upstream:src/simple_network/MainServer.cpp
void startServer()
=======
int NetworkMain()
>>>>>>> Stashed changes:src/simple_network/Networkmain.cpp
{

	// initialize the server
	server = new ServerGame();

	// create thread with arbitrary argument for the run function
    _beginthread( serverLoop, 0, (void*)12);

<<<<<<< Updated upstream:src/simple_network/MainServer.cpp
=======
    // initialize the client 
    client = new ClientGame();

	clientLoop();
	return 0;
>>>>>>> Stashed changes:src/simple_network/Networkmain.cpp
}

void serverLoop(void * arg) 
{ 
    while(true) 
    {
        server->update();
    }
}
