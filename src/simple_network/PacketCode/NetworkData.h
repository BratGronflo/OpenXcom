#pragma once
#include <string.h>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes
{

    INIT_CONNECTION = 0,

    ACTION_EVENT = 1,

	KNEEL_EVENT = 2,

};

class Packet
{
private:
	char data[10000];// BUG: possible buffer overflow
	int cur, size;
 public:
	unsigned int packet_type;
	Packet();
	void reset();
	void serialize(char *data);
		//void serializeBU(OpenXcom::BattleUnit *bu)
		//{
		//    memcpy(bu, this, sizeof(Packet));
		//}
	void deserialize(char *data);
	//void deserializeBU(OpenXcom::BattleUnit *bu)
	//{
    //    memcpy(this, bu, sizeof(Packet));
    //}
	void create(PacketTypes cmd);
	Packet &operator<<(int i);
	Packet &operator>>(int &i);

};

