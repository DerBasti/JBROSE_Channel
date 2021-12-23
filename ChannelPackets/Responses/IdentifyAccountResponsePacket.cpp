#include "IdentifyAccountResponsePacket.h"


IdentifyAccountResponsePacket::IdentifyAccountResponsePacket() : ResponsePacket(IdentifyAccountResponsePacket::ID, IdentifyAccountResponsePacket::DEFAULT_SIZE) {
	unknown1 = 0x00;
	unknown2 = 0x00;
}

IdentifyAccountResponsePacket::~IdentifyAccountResponsePacket() {

}

void IdentifyAccountResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(unknown1);
	sendable.addData(encryptionValue);
	sendable.addData(unknown2);
}