#ifndef _FRIENDLIST_RESPONSE_PACKET__
#define _FRIENDLIST_RESPONSE_PACKET__

#pragma once

#include "..\..\..\JBROSE_Common\Packet.h"

enum class FriendListResponseType : uint8_t {
	SEND_FRIENDLIST = 6
};

class FriendListResponsePacket : public ResponsePacket {
private:
	FriendListResponseType type;
	uint8_t amountOfFriends;
	//FRIENDS
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const {
		sendable.addData(static_cast<uint8_t>(type));
		sendable.addData(amountOfFriends);
		//ACTUAL FRIENDS
	}
public:
	const static uint16_t ID = 0x7E5;


	FriendListResponsePacket() : ResponsePacket(ID) {

	}

	__inline void setFriendlistResponseType(const FriendListResponseType type) {
		this->type = type;
	}

	__inline void setAmountOfFriends(const uint8_t friendsAmount) {
		amountOfFriends = friendsAmount;
	}
};

#endif //_FRIENDLIST_RESPONSE_PACKET__