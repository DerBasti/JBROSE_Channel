#include "WorldServerIpResponsePacket.h"


void WorldServerIpResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(worldServerPort);
	sendable.addData(accountId);
	sendable.addData(encryptionKey);
	sendable.addString(worldServerIp);
}