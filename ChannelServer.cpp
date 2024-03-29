#include "ChannelServer.h"
#include "ChannelPackets\Requests\CharacterCreationRequestPacket.h"

ChannelServer::ChannelServer(uint16_t port) : ROSEServer(port) {
	setPacketFactoryCreatorFunction([]() {
		return std::shared_ptr<PacketFactory>(new ChannelServerPacketFactory());
	});
}

ChannelServer::~ChannelServer() {
	for (std::pair<std::shared_ptr<ROSEClient>, ChannelClient*> pair : clientList) {
		ChannelClient* client = pair.second;

		delete client;
		client = nullptr;
	}
	clientList.clear();
}

void ChannelServer::loadEncryption() {
	ENCRYPTION_TABLE = std::shared_ptr<CryptTable>(new CryptTable());
	ENCRYPTION_TABLE->generateCryptTables();
}

void ChannelServer::onNewROSEClient(std::shared_ptr<ROSEClient>& roseClient) {
	ChannelClient *client = new ChannelClient(roseClient);
	clientList.insert(make_pair(roseClient, client));
}

ChannelClient* ChannelServer::findChannelClientByInterface(std::shared_ptr<ROSEClient>& roseClient) {
	ChannelClient* result = nullptr;
	auto it = clientList.find(roseClient);
	if (it != clientList.cend()) {
		result = (*it).second;
	}
	return result;
}

bool ChannelServer::onPacketsReady(std::shared_ptr<ROSEClient>& roseClient, std::queue<std::shared_ptr<Packet>>& packetQueue) {
	ChannelClient* client = findChannelClientByInterface(roseClient);
	bool success = client != nullptr;
	if (client != nullptr) {
		while (!packetQueue.empty()) {
			std::shared_ptr<Packet> p = packetQueue.front();
			success &= client->handlePacket(p.get());
			packetQueue.pop();
		}
	}
	return success;
}

void ChannelServer::onROSEClientDisconnecting(std::shared_ptr<ROSEClient>& roseClient) {
	ChannelClient* client = findChannelClientByInterface(roseClient);
	if (client != nullptr) {
		clientList.erase(roseClient);
		
		delete client;
		client = nullptr;
	}
}

bool ChannelServer::createNewCharacter(ChannelClient *client, const Packet *packet) {
	const CharacterCreationRequestPacket* requestPacket  = dynamic_cast<const CharacterCreationRequestPacket*>(packet);
	char queryString[0x200] = { 0x00 };

	sprintf_s(queryString, "INSERT INTO players (account_id,player_name,face,hair,sex) VALUES(%i,'%s',%i,%i,%i);",
		client->getAccountId(), requestPacket->getName().c_str(), requestPacket->getFace(), requestPacket->getHair(),
		requestPacket->getSex());
	Database* database = getDatabase();
	logger.logDebug("Adding character with name '", requestPacket->getName().c_str(), " for account #", client->getAccountId());
	int32_t charId = static_cast<int32_t>(database->insertQueryWithIdReturn(queryString, "id"));
	if (charId == -1) {
		logger.logError("Error while creating character: ", database->getLastError());
	}
	else {
		logger.logDebug("Adding basic items...");
		addBasicItemsForNewCharacter(charId, requestPacket->getSex());
	}
	return charId >= 0;
}

bool ChannelServer::addBasicItemsForNewCharacter(int32_t playerId, uint32_t sex) {
	const char *itemQuery = "INSERT INTO items (player_id, item_type, item_id, slot) VALUES(%i, %i, %i, %i);";
	char buf[0x100] = { 0x00 };
	Database* database = getDatabase();
	std::function<bool(int, int, int)> itemInserter = [database, playerId, itemQuery](int type, int id, int slot) -> bool {
		char buf[0x100] = { 0x00 };
		sprintf_s(buf, itemQuery, playerId, id, type, slot);

		return database->insertQuery(buf);
	};

	bool headgearSuccess = itemInserter(2, 1+sex, 14);
	bool weaponSuccess = itemInserter(8, 1, 7);
	bool bodySuccess = itemInserter(3, 1, 3);

	return headgearSuccess && weaponSuccess && bodySuccess;
}

bool ChannelServer::setSelectedCharacter(uint32_t accountId, uint32_t playerId) {
	Database* database = getDatabase();

	char query[0x100] = { 0x00 };
	const char *queryTemplate = "UPDATE accounts SET last_character_online=%i WHERE id=%i";
	sprintf_s(query, queryTemplate, playerId, accountId);
	logger.logDebug("Updating last used character(#", playerId, ") for account: ", accountId);

	return database->updateQuery(query);
}