#include "CharacterListResponsePacket.h"
#include <memory>

CharacterListResponsePacket::CharacterListResponsePacket(uint8_t amount) : ResponsePacket(ID) {
	this->amount = amount;
	characters = std::shared_ptr<ChannelServerCharacter>(new ChannelServerCharacter[amount], std::default_delete<ChannelServerCharacter[]>());
}