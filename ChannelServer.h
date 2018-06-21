#pragma once
#include "..\JBROSE_Common\ROSEServer.h"
#include "ChannelClient.h"
#include "ChannelPackets\ChannelServerPacketFactory.h"

#ifndef __CHANNEL_SERVER__
#define __CHANNEL_SERVER__
#endif

class ChannelServer : public ROSEServer {
private:
	std::unordered_map<ROSEClient*, ChannelClient*> clientList;
	ChannelClient* findChannelClientByInterface(ROSEClient* roseClient);

	static bool addBasicItemsForNewCharacter(int32_t playerId, uint32_t sex);
public:
	ChannelServer(uint16_t port);
	virtual ~ChannelServer();

	virtual void loadEncryption();

	virtual void onNewROSEClient(ROSEClient* roseClient);
	virtual bool onPacketsReady(ROSEClient* client, std::queue<std::shared_ptr<Packet>>& packetQueue);
	virtual void onROSEClientDisconnecting(ROSEClient* client);

	static bool createNewCharacter(ChannelClient *client, const Packet *requestPacket);
	static bool setSelectedCharacter(uint32_t accountId, uint32_t playerId);
};