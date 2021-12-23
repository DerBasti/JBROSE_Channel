#pragma once
#include "..\JBROSE_Common\ROSEServer.h"
#include "ChannelClient.h"
#include "ChannelPackets\ChannelServerPacketFactory.h"

#ifndef __CHANNEL_SERVER__
#define __CHANNEL_SERVER__
#endif

class ChannelServer : public ROSEServer {
private:
	std::unordered_map<std::shared_ptr<ROSEClient>, ChannelClient*> clientList;
	ChannelClient* findChannelClientByInterface(std::shared_ptr<ROSEClient>& roseClient);

	bool addBasicItemsForNewCharacter(int32_t playerId, uint32_t sex);
public:
	ChannelServer(uint16_t port);
	virtual ~ChannelServer();

	virtual void loadEncryption();

	virtual void onNewROSEClient(std::shared_ptr<ROSEClient>& roseClient);
	virtual bool onPacketsReady(std::shared_ptr<ROSEClient>& client, std::queue<std::shared_ptr<Packet>>& packetQueue);
	virtual void onROSEClientDisconnecting(std::shared_ptr<ROSEClient>& client);

	bool createNewCharacter(ChannelClient *client, const Packet *requestPacket);
	bool setSelectedCharacter(uint32_t accountId, uint32_t playerId);

	__inline static ChannelServer* getInstance() {
		return ROSEServer::getInstance<ChannelServer>();
	}
};