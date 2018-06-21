#ifndef __WORLD_SERVER_IP_RESPONSEPACKET__
#define __WORLD_SERVER_IP_RESPONSEPACKET__

#pragma once

#include "..\..\..\JBROSE_Common\Packet.h"

class WorldServerIpResponsePacket : public ResponsePacket {
private:
	uint16_t worldServerPort;
	uint32_t accountId;
	uint32_t encryptionKey;
	std::string worldServerIp;
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const;
public:
	const static uint16_t ID = 0x711;

	WorldServerIpResponsePacket() : ResponsePacket(ID) {
		worldServerPort = 0;
		accountId = encryptionKey = 0;
		worldServerIp.reserve(16);
	}
	virtual ~WorldServerIpResponsePacket() {

	}
	__inline void setWorldServerPort(const uint16_t port) {
		worldServerPort = port;
	}

	__inline void setAccountId(const uint32_t accId) {
		accountId = accId;
	}

	__inline void setEncryptionKey(const uint32_t encryption) {
		encryptionKey = encryption;
	}

	__inline void setWorldServerIp(const std::string& ip) {
		worldServerIp = ip;
	}
};

#endif //__WORLD_SERVER_IP_RESPONSEPACKET__