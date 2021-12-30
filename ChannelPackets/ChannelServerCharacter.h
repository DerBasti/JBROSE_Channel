#pragma once
#ifndef __CHANNELSERVER_CHARACTER__
#define __CHANNELSERVER_CHARACTER__

#include "..\..\JBROSE_Common\Packet.h"
#include "..\..\JBROSE_Common\Database.h"

struct VisibleItem {
	uint16_t id;
	uint16_t refineLevel;

	VisibleItem() {
		id = refineLevel = 0;
	}
};

class ChannelServerCharacter {
private:
	char* name;
	uint32_t id;
	uint8_t sex;
	uint16_t level;
	uint16_t classId;
	uint32_t deleteTimestamp;
	uint8_t premiumStatus;
	uint32_t faceId;
	uint32_t hairstyle;
	VisibleItem items[9];
protected:
public:
	ChannelServerCharacter() {
		name = nullptr;
		sex = premiumStatus = 0;
		level = classId = 0;
		deleteTimestamp = faceId = hairstyle = 0;
		id = -1;
	}
	ChannelServerCharacter(ResultRow* characterResultRow) : ChannelServerCharacter() {
		id = atoi(characterResultRow->getColumnData(0).c_str());

		name = new char[32];
		memset(name, 0x00, 32);
		strncpy_s(name, 32, characterResultRow->getColumnData(2).c_str(), 32);

		level = atoi(characterResultRow->getColumnData(3).c_str());
		classId = atoi(characterResultRow->getColumnData(4).c_str());
		sex = atoi(characterResultRow->getColumnData(5).c_str());
		faceId = atoi(characterResultRow->getColumnData(6).c_str());
		hairstyle = atoi(characterResultRow->getColumnData(7).c_str());
	}
	virtual ~ChannelServerCharacter() {

	}
	ChannelServerCharacter& operator=(const ChannelServerCharacter& other) {
		id = other.id;
		if (name) {
			delete[] name;
			name = nullptr;
		}

		name = new char[32];
		memset(name, 0x00, 32);
		if (other.name != nullptr) {
			strncpy_s(name, 32, other.name, 32);
		}

		level = other.level;
		classId = other.classId;
		sex = other.sex;
		faceId = other.faceId;
		hairstyle = other.hairstyle;
		deleteTimestamp = other.deleteTimestamp;
		premiumStatus = other.premiumStatus;
		for (uint8_t i = 0; i < 9; i++) {
			items[i] = other.items[i];
		}
		return (*this);
	}

	void appendContentToSendable(SendablePacket& sendable) const {
		sendable.addString(name);
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

	__inline const uint32_t getId() const {
		return id;
	}

	__inline const char* getName() const {
		return name;
	}
	__inline uint16_t getLevel() const {
		return level;
	}
	__inline uint16_t getClassId() const {
		return classId;
	}
	__inline uint8_t getSex() const {
		return sex;
	}
	__inline uint32_t getFaceType() const {
		return faceId;
	}
	__inline uint32_t getHairStyle() const {
		return hairstyle;
	}
	__inline uint32_t getDeletionTimestamp() const {
		return deleteTimestamp;
	}
	__inline uint8_t getPremiumStatus() const {
		return premiumStatus;
	}
	__inline const VisibleItem& getVisibleItem(const uint8_t type) const {
		return items[type];
	}
	__inline void setVisibleItem(const uint8_t type, const uint16_t itemId) {
		items[type].id = itemId;
	}

	__inline bool isValid() const {
		return id >= 0;
	}
};

#endif //__CHANNELSERVER_CHARACTER__>	ChannelServer.exe!ChannelServerCharacter::ChannelServerCharacter(ResultRow * characterResultRow) Zeile 53	C++	Symbole wurden geladen.
