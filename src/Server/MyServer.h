#pragma once
#define NOMINMAX
#include <PNet/IncludeMe.h>
#include "../Battlescape/BattlescapeState.h"


class MyServer : public Server

{
public:
	void sendIntPacket(int id);
private:
	void OnConnect(TCPConnection & newConnection) override;
	void OnDisconnect(TCPConnection & lostConnection, std::string reason) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
