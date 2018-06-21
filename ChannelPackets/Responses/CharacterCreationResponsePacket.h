#ifndef __CHARACTER_CREATION_RESPONSEPACKET__
#define __CHARACTER_CREATION_RESPONSEPACKET__

#pragma once

#include "..\..\..\JBROSE_Common\Packet.h"

class CharacterCreationResponsePacket : public ResponsePacket {
private:
	uint16_t responseValue;
	const static uint16_t DEFAULT_SIZE = 8;
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const {
		sendable.addData(responseValue);
	}
public:
	enum class CreationResult : uint16_t {
		CREATION_OKAY,
		CREATION_FAILED_OTHER_FIRST,
		CHARACTER_NAME_EXISTS,
		CREATION_FAILED_OTHER_SECOND,
		CHARLIST_FULL,
		KOREAN_FAILURE,
		CREATION_FAILED
	};
	const static uint16_t ID = 0x713;
	CharacterCreationResponsePacket(const CreationResult& responseValue) : ResponsePacket(ID, DEFAULT_SIZE) {
		this->responseValue = static_cast<uint16_t>(responseValue);
	}
	virtual ~CharacterCreationResponsePacket() {

	}
	
};

#endif //__CHARACTER_CREATION_RESPONSEPACKET__