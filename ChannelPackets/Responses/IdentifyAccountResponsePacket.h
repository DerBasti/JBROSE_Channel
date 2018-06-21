#pragma once
#include "..\..\..\JBROSE_Common\Packet.h"

class IdentifyAccountResponsePacket : public ResponsePacket {
private:
	const static uint16_t DEFAULT_SIZE = 15;

	uint8_t unknown1;
	uint32_t encryptionValue;
	uint32_t unknown2;
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const;
public:
	const static uint16_t ID = 0x70C;
	IdentifyAccountResponsePacket();
	virtual ~IdentifyAccountResponsePacket();

	__inline void setEncryptionValue(const uint32_t value) {
		encryptionValue = value;
	}
};