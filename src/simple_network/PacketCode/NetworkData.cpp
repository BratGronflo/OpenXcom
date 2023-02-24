#pragma once
#include <string.h>
#include "NetworkData.h"
#include <stdio.h>


Packet::Packet()
{
	reset();
}
void Packet::reset()
{
	cur = 0;
	size = 0;
	memset(data, 0, sizeof(data));
}
void Packet::serialize(char *data)

	{
		memcpy(data, this, sizeof(Packet));
	}
void Packet::deserialize(char *data)

	{
        memcpy(this, data, sizeof(Packet));
	}
void Packet::create(PacketTypes cmd)
{
    reset();
    //assert (local.Position >= 1 && local.Position <= 2);
	int len = sprintf(data + size, "_stupidpacket_");
    size += len;
 }
Packet &Packet::operator<<(int id)
{
	int len = sprintf(data + size, "%d_", id);
	size += len;
	return *this;
}
Packet &Packet::operator>>(int &id)
{
	sscanf(data + cur, "%d_", &id);

	int len = 0;
	while (data[cur + len] != '_')
		len++;

	cur += len + 1;
	return *this;
}
