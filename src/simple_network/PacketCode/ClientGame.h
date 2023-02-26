#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include "../../Savegame/BattleUnit.h"

class ClientGame
{
public:
	ClientGame(void);
	~ClientGame(void);

	void sendActionPackets();

    void update();

	void unpackKneelPacket(Packet KneelPacket);

	void sendKneelPackets(int id);

  private:

	ClientNetwork *network;

	char network_data[MAX_PACKET_SIZE];
};

