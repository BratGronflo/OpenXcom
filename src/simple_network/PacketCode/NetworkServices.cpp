#define NOMINMAX
#include "StdAfx.h"
#include "NetworkServices.h"
#include "../../Savegame/BattleUnit.h"

int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
{
    return send(curSocket, message, messageSize, 0);
}

int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
    return recv(curSocket, buffer, bufSize, 0);
}
//int NetworkServices::sendBU(SOCKET curSocket, OpenXcom::BattleUnit *bu, int messageSize)
//{
 //   return send(curSocket, bu, messageSize, 0);
//}

//int NetworkServices::receiveBU(SOCKET curSocket, OpenXcom::BattleUnit *bu, int bufSize)
//{
 //   return recv(curSocket, bu, bufSize, 0);
//}
