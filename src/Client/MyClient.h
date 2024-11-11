#pragma once
#define NOMINMAX
#include <PNet/IncludeMe.h>
//#include "../Battlescape/BattlescapeState.h"
#include "../Engine/Game.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/SavedBattleGame.h"
#include "../Battlescape/BattlescapeGame.h"


class MyClient : public Client
{
  public:
	void SetGame(OpenXcom::Game *);
	void sendIntPacket(int id);
private:
	OpenXcom::Game *_game;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	void OnConnect() override;
	//void OnConnectFail() override;
	//void OnDisconnect(std::string reason) override;
};
