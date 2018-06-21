#ifndef __WORLD_SERVER_IP_REQUESTPACKET__
#define __WORLD_SERVER_IP_REQUESTPACKET__

#pragma once

#include "..\..\..\JBROSE_Common\Packet.h"

class WorldServerIpRequestPacket : public Packet {
private:
	uint8_t unknownByte1;
	uint8_t unknownByte2;
	uint8_t unknownByte3;
	std::string characterName;
	const static uint16_t DEFAULT_SIZE = 9;
public:
	const static uint16_t ID = 0x715;
	WorldServerIpRequestPacket(const Packet* packet) : Packet(ID, DEFAULT_SIZE) {
		const char *ptr = packet->getRawData();
		unknownByte1 = *ptr;
		ptr++;

		unknownByte2 = *ptr;
		ptr++;

		unknownByte3 = *ptr;
		ptr++;

		characterName = std::string(ptr);
	}

	__inline std::string getSelectedCharacter() const {
		return characterName;
	}

	virtual std::string toPrintable() const;
};

#endif