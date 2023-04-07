#pragma once
#define NOMINMAX
#include <PNet/IncludeMe.h>
#include "../Battlescape/BattlescapeState.h"


class MyClient : public Client
{
public:
	void sendIntPacket(int id);
private:
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	void OnConnect() override;
	//void OnConnectFail() override;
	//void OnDisconnect(std::string reason) override;
};
