#include "CharacterCreationRequestPacket.h"

CharacterCreationRequestPacket::CharacterCreationRequestPacket(const Packet *p) : Packet(ID, p->getLength()) {
	const char *data = p->getRawData();
	sex = *data % 2;
	data += 2;
	hair = *data++;
	face = *data;
	data += 4;
	name = std::string(data);
}

CharacterCreationRequestPacket::~CharacterCreationRequestPacket() {

}


std::string CharacterCreationRequestPacket::toPrintable() const {
	char buf[0x100] = { 0x00 };
	sprintf_s(buf, "[CharacterCreationRequestPacket - %i bytes]\n\t* Sex: %i\n\t* Face: %i\n\t* Hair: %i\n\t* Name %s", getLength(), getSex(), getFace(), getHair(), getName().c_str());
	return std::string(buf);
}