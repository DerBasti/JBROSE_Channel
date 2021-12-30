#include "CharacterListResponsePacket.h"
#include <memory>

CharacterListResponsePacket::CharacterListResponsePacket(uint8_t amount) : ResponsePacket(ID) {
	this->amount = amount;
}