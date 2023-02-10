#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "../../Savegame/BattleUnit.h"

class NetworkServices
{
public:
	static int sendMessage(SOCKET curSocket, char * message, int messageSize);
	static int receiveMessage(SOCKET curSocket, char * buffer, int bufSize);
	//static int sendBU(SOCKET curSocket,OpenXcom::BattleUnit *bu, int messageSize);
	//-static int receiveBU(SOCKET curSocket,OpenXcom::BattleUnit *bu, int bufSize);
};

