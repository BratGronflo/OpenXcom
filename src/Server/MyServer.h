#pragma once
#define NOMINMAX
#include <PNet/IncludeMe.h>
//#include "../Battlescape/BattlescapeState.h"
#include "../Engine/Game.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/SavedBattleGame.h"
#include "../Battlescape/BattlescapeGame.h"


class MyServer : public Server

{
public:
	void SetGame(OpenXcom::Game*);
	void sendIntPacket(int id);
private:
	OpenXcom::Game* _game;
	void OnConnect(TCPConnection & newConnection) override;
	void OnDisconnect(TCPConnection & lostConnection, std::string reason) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};

