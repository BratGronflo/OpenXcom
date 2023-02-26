#define NOMINMAX
#include "StdAfx.h"
#include "ClientGame.h"
#include "../../Battlescape/BattlescapeGame.h"

ClientGame::ClientGame(void)
{

    network = new ClientNetwork();

    // send init packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = INIT_CONNECTION;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


ClientGame::~ClientGame(void)
{
}

void ClientGame::sendActionPackets()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

    packet.serialize(packet_data);

    NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update()
{
    Packet packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
        return;
    }

    int i = 0;
    while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(Packet);

        switch (packet.packet_type)
		{
		    case KNEEL_EVENT:
			printf("client RECEIVED Kneel packet from server\n");
			unpackKneelPacket(packet);
			printf("client UNPACKED Kneel packet from server\n");
			//sendActionPackets();

			    break;

			case INIT_CONNECTION:

			printf("client received INIT event packet from server\n");

			//sendActionPackets();

			    break;

            case ACTION_EVENT:

                printf("client received action event packet from server\n");

                //sendActionPackets();

                break;

            default:

                printf("error in packet types\n");

                break;
        }
    }
}
/*void ClientGame::sendKneelPackets(int id)
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = KNEEL_EVENT;
	packet << id;
	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}
*/
void ClientGame::unpackKneelPacket(Packet KneelPacket)
{
	int id;
	id = 0;
	KneelPacket >> id;
	OpenXcom::BattlescapeGame *BG = {};
	BG->ClientKneel(id);
}
