#pragma once
#include <string.h>
#include "../../Savegame/BattleUnit.h"

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {

    INIT_CONNECTION = 0,

    ACTION_EVENT = 1,

	KNEEL_EVENT = 2,

};
struct Packet
{

	char data[100000];
	int cur, size;
    unsigned int packet_type;

    void serialize(char * data)
	{
        memcpy(data, this, sizeof(Packet));
    }
    //void serializeBU(OpenXcom::BattleUnit *bu)
	//{
    //    memcpy(bu, this, sizeof(Packet));
    //}
    void deserialize(char * data)
	{
        memcpy(this, data, sizeof(Packet));
    }
	//void deserializeBU(OpenXcom::BattleUnit *bu)
	//{
    //    memcpy(this, bu, sizeof(Packet));
    //}
Packet &operator<<(OpenXcom::BattleUnit *bu)
	{
		int len = sprintf(data + size, "%p", bu);
		size += len;
		return *this;
	}
Packet &operator>>(OpenXcom::BattleUnit *bu)
	{
		sscanf(data + cur, "%p", &bu);

		int len = 0;
		while (data[cur + len] != '_')
			len++;

		cur += len + 1;
		return *this;
	}
};
