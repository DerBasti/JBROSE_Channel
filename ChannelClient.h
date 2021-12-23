#pragma once
#include "..\JBROSE_Common\ROSEClient.h"
#include "..\JBROSE_Channel\ChannelPackets\ChannelServerCharacter.h"

class ChannelClient {
private:
	std::shared_ptr<ROSEClient> connectionWrapper;
	uint32_t accountId;
	ROSELogger logger;
	ChannelServerCharacter characters[5];

	ChannelServerCharacter getCharacterFromName(const std::string& name) const;

	bool handleIdentification(const Packet* packet);
	bool handleGetCharacterList(const Packet* packet);
	bool handleCharacterCreation(const Packet* packet);
	bool handleWorldServerIpRequest(const Packet* packet);

	__inline std::shared_ptr<ROSEClient> getConnectionWrapper() const {
		return connectionWrapper;
	}
	void setItemsForCharacter(ChannelServerCharacter& character);
public:
	ChannelClient(std::shared_ptr<ROSEClient>& roseClient);
	virtual ~ChannelClient();

	bool handlePacket(const Packet* packet);

	__inline uint32_t getAccountId() const {
		return accountId;
	}
};