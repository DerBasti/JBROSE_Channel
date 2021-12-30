#include "ChannelClient.h"
#include "ChannelPackets.h"
#include "..\JBROSE_Common\EncryptionHandler.h"
#include "ChannelServer.h"
#include <iostream>

ChannelClient::ChannelClient(std::shared_ptr<ROSEClient>& roseClient) {
	connectionWrapper = roseClient;
	for (uint8_t i = 0; i < 5; i++) {
		this->characters[i] = ChannelServerCharacter();
	}
}

ChannelClient::~ChannelClient() {
}

bool ChannelClient::handleIdentification(const Packet* packet) {
	const IdentifyAccountRequestPacket *request = dynamic_cast<const IdentifyAccountRequestPacket*>(packet);
	accountId = request->getAccountId();

	IdentifyAccountResponsePacket response;
	response.setEncryptionValue(CryptTable::DEFAULT_CRYPTTABLE_START_VALUE);

	return getConnectionWrapper()->sendData(response);
}

bool ChannelClient::handleGetCharacterList(const Packet* packet) {
	ChannelServer* server = ChannelServer::getInstance();
	Database* database = server->getDatabase();
	char query[0x150] = { 0x00 };
	sprintf_s(query, "SELECT * FROM players WHERE account_id=%i", accountId);
	auto result = database->selectQuery(query);
	CharacterListResponsePacket packetToSend;
	if (result) {
		uint32_t amount = result->getResultAmount();
		packetToSend.setCharacterAmount(static_cast<uint8_t>(amount));
		for (uint32_t i = 0; i < amount; i++) {
			ResultRow *row = result->getRow(i);
			characters[i] = ChannelServerCharacter(row);
			setItemsForCharacter(characters[i]);
			packetToSend.addCharacter(characters[i], i);
		}
	}
	return getConnectionWrapper()->sendData(packetToSend);
}

void ChannelClient::setItemsForCharacter(ChannelServerCharacter& character) {
	char query[0x150] = { 0x00 };
	sprintf_s(query, "SELECT slot, item_id, refinement FROM items WHERE player_id=%i AND slot<=8", character.getId());
	Database* database = ChannelServer::getInstance()->getDatabase();
	auto result = database->selectQuery(query);
	if (result) {
		uint32_t amount = result->getResultAmount();
		for (uint32_t i = 0; i < amount; i++) {
			ResultRow *row = result->getRow(i);
			character.setVisibleItem(atoi(row->getColumnData(0).c_str()), 
				atoi(row->getColumnData(1).c_str()));;
		}
	}
}

bool ChannelClient::handleCharacterCreation(const Packet* packet) {
	const CharacterCreationRequestPacket* requestPacket = dynamic_cast<const CharacterCreationRequestPacket*>(packet);
	char query[0x150] = { 0x00 };
	sprintf_s(query, "SELECT id FROM players WHERE player_name='%s'", requestPacket->getName().c_str());
	auto result = ChannelServer::getInstance()->getDatabase()->selectQuery(query);
	if (result->hasResult()) {
		CharacterCreationResponsePacket response(CharacterCreationResponsePacket::CreationResult::CHARACTER_NAME_EXISTS);
		return getConnectionWrapper()->sendData(response);
	}
	bool success = ChannelServer::getInstance()->createNewCharacter(this, requestPacket);
	CharacterCreationResponsePacket response(success == true ? CharacterCreationResponsePacket::CreationResult::CREATION_OKAY : CharacterCreationResponsePacket::CreationResult::CREATION_FAILED);
	return getConnectionWrapper()->sendData(response);
}

bool ChannelClient::handleWorldServerIpRequest(const Packet* packet) {
	const WorldServerIpRequestPacket* requestPacket = dynamic_cast<const WorldServerIpRequestPacket*>(packet);
	std::string selectedCharacterName = requestPacket->getSelectedCharacter();

	const ChannelServerCharacter& character = getCharacterFromName(selectedCharacterName);
	if (!character.isValid()) {
		logger.logError("Character '", selectedCharacterName.c_str(), "' not found!");
		return false;
	}
	//			Datenbank updaten mit ID
	//			WorldServer-Packet senden

	if (!ChannelServer::getInstance()->setSelectedCharacter(this->getAccountId(), character.getId())) {
		logger.logError("Character '", selectedCharacterName.c_str(), "' couldn't be assigned as last logged-in!");
		return false;
	}

	WorldServerIpResponsePacket response;
	response.setWorldServerIp("127.0.0.1");
	response.setWorldServerPort(29200);
	response.setAccountId(getAccountId());
	response.setEncryptionKey(CryptTable::DEFAULT_CRYPTTABLE_START_VALUE);
	
	FriendListResponsePacket friendResponse;
	friendResponse.setFriendlistResponseType(FriendListResponseType::SEND_FRIENDLIST);
	friendResponse.setAmountOfFriends(0);

	return getConnectionWrapper()->sendData(response) && getConnectionWrapper()->sendData(friendResponse);
}

ChannelServerCharacter ChannelClient::getCharacterFromName(const std::string& name) const {
	for (uint8_t i = 0; i < 5; i++) {
		const ChannelServerCharacter& character = characters[i];
		if (_stricmp(character.getName(), name.c_str()) == 0) {
			return character;
		}
	}
	return ChannelServerCharacter();
}

bool ChannelClient::handlePacket(const Packet* packet) {
	bool success = false;
	switch (packet->getCommandId()) {
		case IdentifyAccountRequestPacket::ID:
			success = handleIdentification(packet);
		break;
		case CharacterListRequestPacket::ID:
			success = handleGetCharacterList(packet);
		break;
		case CharacterCreationRequestPacket::ID:
			success = handleCharacterCreation(packet);
		break;
		case WorldServerIpRequestPacket::ID:
			success = handleWorldServerIpRequest(packet);
		break;
		default:
			logger.logWarn("Unknown packet: ", packet->toPrintable().c_str());
	}
	return success;
}