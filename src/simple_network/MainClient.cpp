// main.cpp : Defines the entry point for the console application.
//

// may need #include "stdafx.h" in visual studio
#include "stdafx.h"
#include "ClientGame.h"
// used for multi-threading
#include <process.h>

void clientLoop(void);

ClientGame * client;

void startClient()
{

    // initialize the client 
    client = new ClientGame(); // Jopper Step 1

	clientLoop();
}

void clientLoop()
{
    while(true)
    {
        //do game stuff
        client->update();
    }
}
