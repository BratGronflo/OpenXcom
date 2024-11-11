#include "MyClient.h"
#include <iostream>
#include <string> 

void MyClient::SetGame(OpenXcom::Game *game)
{
	_game = game;
}

bool MyClient::ProcessPacket(std::shared_ptr<Packet> packet)
{
	switch (packet->GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::string chatmessage;
		*packet >> chatmessage;
		std::cout << "Chat Message: " << chatmessage << std::endl;
		break;
	}
	case PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		*packet >> arraySize;
		std::cout << "Array Size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			*packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	case PacketType::PT_UnitID:
	{
		std::string strUnitId;
		*packet >> strUnitId;
		int UnitId = stoi(strUnitId); // Jopper if error occurs, then the int is too long, use std::stol intsead;
		/*OpenXcom::BattlescapeState clientBattleState;
		clientBattleState.kneelDamnIt(UnitId);*/
		std::string checkUnitId = std::to_string(UnitId);
		std::cout << "Unit Id: " << UnitId << std::endl;

		break;

	}
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

void MyClient::OnConnect()
{
	std::cout << "Successfully connected to the server!" << std::endl;

	std::shared_ptr<Packet> helloPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*helloPacket << std::string("Hello from the client!");
	connection.pm_outgoing.Append(helloPacket);
}
void MyClient::sendIntPacket(int id)
{
	std::string UnitId = std::to_string(id);

	std::shared_ptr<Packet>UnitIdPacket = std::make_shared<Packet>(PacketType::PT_UnitID);
	*UnitIdPacket << std::string(UnitId);
	connection.pm_outgoing.Append(UnitIdPacket);
}
