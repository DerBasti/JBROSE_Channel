#ifndef __CHARACTER_CREATION_REQUESTPACKET__
#define __CHARACTER_CREATION_REQUESTPACKET__

#include "..\..\..\JBROSE_Common\Packet.h"

class CharacterCreationRequestPacket : public Packet {
private:
	uint8_t sex;
	uint8_t face;
	uint8_t hair;
	std::string name;
public:
	const static uint16_t ID = 0x713;
	CharacterCreationRequestPacket(const Packet *p);
	virtual ~CharacterCreationRequestPacket();


	std::string toPrintable() const;

	uint8_t getSex() const {
		return sex;
	}
	uint8_t getFace() const {
		return face;
	}
	uint8_t getHair() const {
		return hair;
	}
	std::string getName() const {
		return name;
	}
};

#endif //__CHARACTER_CREATION_REQUESTPACKET__