#ifndef _FRIENDLIST_RESPONSE_PACKET__
#define _FRIENDLIST_RESPONSE_PACKET__

#pragma once

#include "..\..\..\JBROSE_Common\Packet.h"

class FriendListResponsePacket : public ResponsePacket {
private:
	uint8_t type;
	uint8_t amountOfFriends;
	//FRIENDS
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const {
		sendable.addData(type);
		sendable.addData(amountOfFriends);
		//ACTUAL FRIENDS
	}
public:
	const static uint16_t ID = 0x7E5;

	FriendListResponsePacket() : ResponsePacket(ID) {

	}

	__inline void setAmountOfFriends(const uint8_t friendsAmount) {
		amountOfFriends = friendsAmount;
	}
};

#endif //_FRIENDLIST_RESPONSE_PACKET__