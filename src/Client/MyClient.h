#pragma once
#include "../PNet/IncludeMe.h"

class MyClient : public Client
{
	void sendIntPacket();
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	void OnConnect() override;
	//void OnConnectFail() override;
	//void OnDisconnect(std::string reason) override;
};