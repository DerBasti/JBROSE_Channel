#pragma once
#ifndef __CHANNELSERVER_CHARACTER__
#define __CHANNELSERVER_CHARACTER__

#include "..\..\JBROSE_Common\Packet.h"
#include "..\..\JBROSE_Common\Database.h"

class ChannelServerCharacter : public ResponsePacket {
private:
	std::string name;
	uint32_t id;
	uint8_t sex;
	uint16_t level;
	uint16_t classId;
	uint32_t deleteTimestamp;
	uint8_t premiumStatus;
	uint32_t faceId;
	uint32_t hairstyle;

	struct VisibleItem {
		uint16_t id;
		uint16_t refineLevel;

		VisibleItem() {
			id = refineLevel = 0;
		}
	} items[8];
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const {
		sendable.addString(name.c_str());
		sendable.addData(sex);
		sendable.addData(level);
		sendable.addData(classId);
		sendable.addData(deleteTimestamp);
		sendable.addData(premiumStatus);
		sendable.addData(faceId);
		sendable.addData(hairstyle);
		std::function<void(int)> itemAppender = [&](int slot) {
			sendable.addData(items[slot].id);
			sendable.addData(items[slot].refineLevel);
		};
		itemAppender(2); itemAppender(3);
		itemAppender(5); itemAppender(6);
		itemAppender(1); itemAppender(4);
		itemAppender(7); itemAppender(8);
	}
public:
	ChannelServerCharacter() : ResponsePacket(-1, 0x00) {
		sex = premiumStatus = 0;
		level = classId = 0;
		deleteTimestamp = faceId = hairstyle = 0;
		id = -1;
	}
	ChannelServerCharacter(ResultRow* characterResultRow) : ChannelServerCharacter() {
		id = atoi(characterResultRow->getColumnData(0).c_str());
		name = characterResultRow->getColumnData(2);
		level = atoi(characterResultRow->getColumnData(3).c_str());
		classId = atoi(characterResultRow->getColumnData(4).c_str());
		sex = atoi(characterResultRow->getColumnData(5).c_str());
		faceId = atoi(characterResultRow->getColumnData(6).c_str());
		hairstyle = atoi(characterResultRow->getColumnData(7).c_str());
	}
	virtual ~ChannelServerCharacter() {

	}

	__inline const uint32_t getId() const {
		return id;
	}

	__inline const std::string& getName() const {
		return name;
	}

	__inline void setVisibleItem(const uint8_t type, const uint16_t itemId) {
		items[type].id = itemId;
	}

	__inline bool isValid() const {
		return id >= 0;
	}
};

#endif //__CHANNELSERVER_CHARACTER__>	ChannelServer.exe!ChannelServerCharacter::ChannelServerCharacter(ResultRow * characterResultRow) Zeile 53	C++	Symbole wurden geladen.
