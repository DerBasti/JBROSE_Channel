#pragma once
#ifndef __GET_CHARACTER_REQUEST_PACKET__
#define __GET_CHARACTER_REQUEST_PACKET__

#include "..\..\..\JBROSE_Common\Packet.h"
#include "..\ChannelServerCharacter.h"

class CharacterListRequestPacket : public Packet {
private:
public:
	const static uint16_t ID = 0x712;
	CharacterListRequestPacket(const Packet* packet) : Packet(CharacterListRequestPacket::ID, 6) {}
	virtual ~CharacterListRequestPacket() {}

	std::string toPrintable() const {
		char buf[0x100] = { 0x00 };
		sprintf_s(buf, "[CharacterListRequestPacket - %i bytes]", getLength());
		return std::string(buf);
	}
};

#endif //__GET_CHARACTER_REQUEST_PACKET__