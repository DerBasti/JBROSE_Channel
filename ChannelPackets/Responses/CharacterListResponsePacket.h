#pragma once
#ifndef __GET_CHARACTER_RESPONSE_PACKET__
#define __GET_CHARACTER_RESPONSE_PACKET__

#include "..\..\..\JBROSE_Common\MySQLDatabase.h"
#include "..\..\..\JBROSE_Common\Packet.h"
#include "..\ChannelServerCharacter.h"

class CharacterListResponsePacket : public ResponsePacket {
private:
	uint8_t amount;
	ChannelServerCharacter characters[5];
public:
	const static uint16_t ID = 0x712;
	CharacterListResponsePacket() : CharacterListResponsePacket(0) {}
	CharacterListResponsePacket(uint8_t characterAmount);
	virtual ~CharacterListResponsePacket() {}

	__inline void setCharacterAmount(const uint8_t amount) {
		this->amount = amount;
	}

	__inline void addCharacter(const ChannelServerCharacter& character, uint8_t idx) {
		characters[idx] = character;
	}

	void appendContentToSendable(SendablePacket& sendable) const {
		sendable.addData(amount);
		for (uint16_t idx = 0; idx < amount; idx++) {
			const ChannelServerCharacter& character = characters[idx];
			character.appendContentToSendable(sendable);
		}
	}

	std::string toPrintable() const {
		char buf[0x100] = { 0x00 };
		sprintf_s(buf, "[CharacterListResponsePacket - %i + Character bytes]\n\t* Character Amount: %i", getLength(), amount);
		return std::string(buf);
	}
};

#endif //__GET_CHARACTER_RESPONSE_PACKET__