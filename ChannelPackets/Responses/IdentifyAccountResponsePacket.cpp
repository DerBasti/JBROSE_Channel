#include "IdentifyAccountResponsePacket.h"


IdentifyAccountResponsePacket::IdentifyAccountResponsePacket() : ResponsePacket(IdentifyAccountResponsePacket::ID, IdentifyAccountResponsePacket::DEFAULT_SIZE) {

}

IdentifyAccountResponsePacket::~IdentifyAccountResponsePacket() {

}

void IdentifyAccountResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(unknown1);
	sendable.addData(encryptionValue);
	sendable.addData(unknown2);
}